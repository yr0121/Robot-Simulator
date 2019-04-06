/**
 * @file braitenberg_vehicle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BRAITENBERG_VEHICLE_H_
#define SRC_BRAITENBERG_VEHICLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/* @brief Entity class to represent a Braitenberg Vehicle
 *
 * A braitenberg vehicle is a simple machine that is used to show how simple
 * concepts (in this case wiring) can give way to complex looking behavior. In
 * this simulation, Braitenberg vehicles contain sensors, which can be hooked
 * up in four different ways, and thus they can exhibit four different behaviors
 */

class BraitenbergVehicle : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  BraitenbergVehicle();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  BraitenbergVehicle(const BraitenbergVehicle & rhs) = delete;
  BraitenbergVehicle operator=(const BraitenbergVehicle & rhs) = delete;

  /**
   * @brief Update the BraitenbergVehicle's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

    /**
     * @brief Method for updating the velocity of braitenberg vehicles
     * It checks the food and light behavior and change sensor readings
     * According to sensor reading, change the velocity of braitenberg vehicle
     * Then based on the presence of light and food behavior, change the color of braitenberg vehicle
     */
  void Update() override;

  /**
   * @brief Change the movement state of the BraitenbergVehicle.
   * the robot will turn 180 degrees first, move 20 timesteps and
   * turn 45 degrees
   */
  void HandleCollision(EntityType ent_type,
                       ArenaEntity * object = NULL) override;

  /**
   * @brief find the closest entity around braitenberg vehicle
   * @param entity a place holder for finded closest entity
   */
  void SenseEntity(const ArenaEntity& entity);

  std::string get_name() const override;

  std::vector<Pose> get_light_sensors_const() const;

  std::vector<Pose> get_light_sensors();

  void UpdateLightSensors();

  /**
   * @brief assign the values in json to the object
   * @param entity_config a pointer points to json object
   */
  void LoadFromObject(json_object* entity_config) override;

  Behavior get_light_behavior() { return light_behavior_; }

  void set_light_behavior(Behavior behavior) { light_behavior_ = behavior; }

  Behavior get_food_behavior() { return food_behavior_; }

  void set_food_behavior(Behavior behavior) { food_behavior_ = behavior; }

  double get_sensor_reading_left(const ArenaEntity* entity);

  double get_sensor_reading_right(const ArenaEntity* entity);

  static int count;

 private:
  std::vector<Pose> light_sensors_;
  MotionBehaviorDifferential * motion_behavior_{nullptr};
  WheelVelocity wheel_velocity_;
  Behavior light_behavior_;
  Behavior food_behavior_;
  const ArenaEntity* closest_light_entity_;
  const ArenaEntity* closest_food_entity_;
  double defaultSpeed_;
  bool is_collision_;
  int counter_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BRAITENBERG_VEHICLE_H_
