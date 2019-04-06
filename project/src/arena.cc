/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>

#include "src/arena.h"
#include "src/light.h"
#include "src/braitenberg_vehicle.h"
#include "src/factory.h"
#include "src/food_factory.h"
#include "src/light_factory.h"
#include "src/braitenberg_factory.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

Arena::Arena(): x_dim_(X_DIM),
      y_dim_(Y_DIM),
      entities_(),
      mobile_entities_() {
    AddEntity(new Light());
    AddEntity(new Food());
    AddEntity(new BraitenbergVehicle());
}

Arena::Arena(json_object* arena_object_pointer): x_dim_(X_DIM),
      y_dim_(Y_DIM),
      entities_(),
      mobile_entities_() {
  json_object &arena_object = *arena_object_pointer;
  x_dim_ = arena_object["width"].get<double>();
  y_dim_ = arena_object["height"].get<double>();

  json_array& entities = arena_object["entities"].get<json_array>();
  for (unsigned int f = 0; f < entities.size(); f++) {
    json_object& entity_config = entities[f].get<json_object>();
    EntityType etype = get_entity_type(
      entity_config["type"].get<std::string>());

    ArenaEntity* entity = NULL;
    // create a factory pointer,determine the type of entity to be created
    // use dynamic binding to create derived class instance
    // and produce corresponding object
    Factory *factory;
    switch (etype) {
      case (kLight):
        factory = new LightFactory();
        entity = factory->create(&entity_config);
        break;
      case (kFood):
        factory = new FoodFactory();
        entity = factory->create(&entity_config);
        break;
      case (kBraitenberg):
        factory = new BraitenbergFactory();
        entity = factory->create(&entity_config);
        break;
      default:
        std::cout << "FATAL: Bad entity type on creation" << std::endl;
        assert(false);
    }
      AddEntity(entity);
    }
  }


Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Arena::AddEntity(ArenaEntity* ent) {
  entities_.push_back(ent);
  if (ent->is_mobile()) {
    auto mob_ent = static_cast<ArenaMobileEntity*>(ent);
    mobile_entities_.push_back(mob_ent);
  }

  BraitenbergVehicle* bv = dynamic_cast<BraitenbergVehicle*>(ent);
  if (bv) {
    bv->UpdateLightSensors();
  }
}

void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   * Should this be just the mobile entities ??
   *  ^^ Nope, I use TimestepUpdate on all entities now (to update sensors)
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }

   /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  for (auto &ent1 : mobile_entities_) {
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
      ent1->HandleCollision(wall);
    }
    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        // if a braitenberg vehicle collides with food, call consume on bv
        // this is pretty ugly, I should move it into HandleCollision
        if (ent1->get_type() == kBraitenberg &&
            ent2->get_type() == kFood) {
          // static_cast<BraitenbergVehicle*>(ent1)->ConsumeFood();
        } else if (ent1->get_type() == kFood &&
                   ent2->get_type() == kBraitenberg) {
          // static_cast<BraitenbergVehicle*>(ent2)->ConsumeFood();
        }
        // lights and braitenberg vehicles do not collide
        // nothing collides with food, but bv's call consume() if they do
        if ((ent2->get_type() == kBraitenberg && ent1->get_type() == kLight) ||
            (ent2->get_type() == kLight && ent1->get_type() == kBraitenberg) ||
            (ent2->get_type() == kFood) || (ent1->get_type() == kFood)     ) {
          continue;
        }
        AdjustEntityOverlap(ent1, ent2);
        ent1->HandleCollision(ent2->get_type(), ent2);
      }
    }

    if (ent1->get_type() == kBraitenberg) {
      BraitenbergVehicle* bv = static_cast<BraitenbergVehicle*>(ent1);
      for (unsigned int f = 0; f < entities_.size(); f++) {
        bv->SenseEntity(*entities_[f]);
      }

      bv->Update();
    }
  }
}  // UpdateEntitiesTimestep()

// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
/* @TODO: Add to Pose distance distance_between (e.g. overload operator -)
*/
/* @BUG: The robot will pass through the home food on occasion. The problem
 * is likely due to the adjustment being in the wrong direction. This could
 * be because the cos/sin generate the wrong sign of the distance_to_move
 * when the collision is in a specific quadrant relative to the center of the
 * colliding entities..
 */
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between;
    double angle = atan2(delta_y, delta_x);
    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

NAMESPACE_END(csci3081);
