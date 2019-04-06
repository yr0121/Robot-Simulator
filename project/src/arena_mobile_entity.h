/**
 * @file arena_mobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the Arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the GraphicsArenaViewer.
 *
 * Since this is also a food class, many of its methods are intuitively
 * `virtual`.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  /**
   * @brief ArenaMobileEntity's constructor.
   */

  ArenaMobileEntity()
    : ArenaEntity(),
      speed_(0),
      is_moving_(true) {
        set_mobility(true);
  }
  ArenaMobileEntity(const ArenaMobileEntity& other) = delete;
  ArenaMobileEntity& operator=(const ArenaMobileEntity& other) = delete;

  virtual void HandleCollision(__unused EntityType ent_type,
                               __unused ArenaEntity * object = NULL) { }

  virtual double get_speed() { return speed_; }
  virtual void set_speed(double sp) { speed_ = sp; }

  bool is_moving() { return is_moving_; }
  void set_is_moving(bool moving) { is_moving_ = moving; }


 private:
  double speed_;
  bool is_moving_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
