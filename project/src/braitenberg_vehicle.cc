       /**
 * @file braitenberg_vehicle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/braitenberg_vehicle.h"
#include "src/params.h"
#include "src/rgb_color.h"

class SensorLightLove;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int BraitenbergVehicle::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

BraitenbergVehicle::BraitenbergVehicle() :
  light_sensors_(), wheel_velocity_(), light_behavior_(kNone),
  food_behavior_(kNone), closest_light_entity_(NULL),
  closest_food_entity_(NULL), defaultSpeed_(5.0),
  is_collision_(false), counter_(0) {
  set_type(kBraitenberg);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(BRAITENBERG_COLOR);
  set_pose(ROBOT_INIT_POS);

  wheel_velocity_ = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);
}

void BraitenbergVehicle::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
    motion_behavior_->UpdatePose(dt, wheel_velocity_);
  }
  UpdateLightSensors();
  if (counter_ < 20 && is_collision_ == true) {
    counter_++;
  }
  // if timestep is 20 and robot hits the wall,
  // set the direction to turn 45 degrees
  // and reset the counter and conditional variable
  if (counter_  ==20 && is_collision_ == true) {
    set_heading(static_cast<int>((get_pose().theta+180+45)) % 360);
    counter_ = 0;
    is_collision_ = false;
  }
}

void BraitenbergVehicle::HandleCollision(__unused EntityType ent_type,
                                         __unused ArenaEntity * object) {
  // reset the velocity and turn 180,
  // set conditional variable to indicate the robot had a collision
  wheel_velocity_ = WheelVelocity(1.0, 1.0);
  set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
  is_collision_ = true;
}

void BraitenbergVehicle::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  }

  if (!closest_entity_) {
    return;
  }

  if (!*closest_entity_) {
    *closest_entity_ = &entity;
  }

  double distance = (this->get_pose()-entity.get_pose()).Length();
  double closest_distance =
  (this->get_pose()-(*closest_entity_)->get_pose()).Length();
  if (distance < closest_distance) {
    *closest_entity_ = &entity;
    closest_distance = distance;
  }
  if (closest_distance > 100.0) {
    *closest_entity_ = NULL;
  }
}

void BraitenbergVehicle::Update() {
  WheelVelocity light_wheel_velocity = WheelVelocity(0, 0);

  int numBehaviors = 2;
  // check light behavior to change sensor reading
  switch (light_behavior_) {
    case kExplore:
      light_wheel_velocity = WheelVelocity(
        1.0/get_sensor_reading_right(closest_light_entity_),
         1.0/get_sensor_reading_left(closest_light_entity_), defaultSpeed_);
      break;
    case kNone:
      light_wheel_velocity = WheelVelocity(0, 0);
      break;
    case kLove:
      light_wheel_velocity = WheelVelocity(
        1.0/get_sensor_reading_left(closest_light_entity_),
        1.0/get_sensor_reading_right(closest_light_entity_), defaultSpeed_);
      break;
    case kAggressive:
      light_wheel_velocity = WheelVelocity(
        get_sensor_reading_right(closest_light_entity_),
        get_sensor_reading_left(closest_light_entity_), defaultSpeed_);
      break;
    case kCoward:
      light_wheel_velocity = WheelVelocity(
         get_sensor_reading_left(closest_light_entity_),
         get_sensor_reading_right(closest_light_entity_), defaultSpeed_);
      break;
    default:
      numBehaviors--;
      break;
  }

  WheelVelocity food_wheel_velocity = WheelVelocity(0, 0);
  // check food behavior to change senor reading
  switch (food_behavior_) {
    case kExplore:
      food_wheel_velocity = WheelVelocity(
        1.0/get_sensor_reading_right(closest_food_entity_),
        1.0/get_sensor_reading_left(closest_food_entity_), defaultSpeed_);
      break;
    case kNone:
      food_wheel_velocity = WheelVelocity(0, 0);
      break;
    case kLove:
      food_wheel_velocity = WheelVelocity(
          1.0/get_sensor_reading_left(closest_food_entity_),
          1.0/get_sensor_reading_right(closest_food_entity_), defaultSpeed_);
      break;
    case kAggressive:
      food_wheel_velocity = WheelVelocity(
          get_sensor_reading_right(closest_food_entity_),
          get_sensor_reading_left(closest_food_entity_), defaultSpeed_);
      break;
    case kCoward:
      food_wheel_velocity = WheelVelocity(
           get_sensor_reading_left(closest_food_entity_),
           get_sensor_reading_right(closest_food_entity_), defaultSpeed_);
      break;
    default:
      numBehaviors--;
      break;
  }
  // create 3 color object
  RgbColor m = RgbColor(122, 0, 25);
  RgbColor b = RgbColor(0, 0, 225);
  RgbColor g = RgbColor(255, 204, 51);
  // change the robot color based on the presence of light and food behavior
  if (food_behavior_ == kNone && light_behavior_ == kNone) {
    set_color(m);
  }

  if (food_behavior_ == kNone && light_behavior_ != kNone) {
    set_color(g);
  }

  if (food_behavior_ != kNone && light_behavior_ != kNone) {
    set_color(m);
  }

  if (food_behavior_ != kNone && light_behavior_ == kNone) {
    set_color(b);
  }

  if (numBehaviors) {
    wheel_velocity_ = WheelVelocity(
      (light_wheel_velocity.left + food_wheel_velocity.left)/numBehaviors,
      (light_wheel_velocity.right + food_wheel_velocity.right)/numBehaviors,
      defaultSpeed_);
  } else {
    wheel_velocity_ = WheelVelocity(0, 0);
  }
}

std::string BraitenbergVehicle::get_name() const {
  return "Braitenberg " + std::to_string(get_id());
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors() {
  return light_sensors_;
}

double BraitenbergVehicle::get_sensor_reading_left(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[0]).Length());
  }

  return 0.0001;
}

double BraitenbergVehicle::get_sensor_reading_right(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[1]).Length());
  }

  return 0.0001;
}

void BraitenbergVehicle::UpdateLightSensors() {
  for (unsigned int f = 0; f < light_sensors_.size(); f++) {
    Pose& pos = light_sensors_[f];
    if (f == 0) {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta - 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta - 40));
    } else {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta + 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta + 40));
    }
  }
}

void BraitenbergVehicle::LoadFromObject(json_object* entity_config_pointer) {
  ArenaEntity::LoadFromObject(entity_config_pointer);
  json_object &entity_config = *entity_config_pointer;
  if (entity_config.find("light_behavior") != entity_config.end()) {
      light_behavior_ = get_behavior_type(
        entity_config["light_behavior"].get<std::string>());
  }
  if (entity_config.find("food_behavior") != entity_config.end()) {
      food_behavior_ = get_behavior_type(
        entity_config["food_behavior"].get<std::string>());
  }

  UpdateLightSensors();
}

NAMESPACE_END(csci3081);
