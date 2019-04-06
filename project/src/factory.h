/**
 * @file factory.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FACTORY_H_
#define SRC_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/arena_entity.h"
#include "src/food.h"
#include "src/light.h"
#include "src/braitenberg_vehicle.h"



/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for creating various kinds of entities
  * It handles the correct production of food, light and braitenberg vehicle
  *
  */
class Factory {
 public:
  /**
    * @brief Factory's constructor.
  */
  Factory(void) {}
  /**
   * @brief Factory's destructor. `delete` all factories created.
   */
  virtual ~Factory(void) = default;

  /**
   * @brief copy constructor
   */
  Factory(const Factory &F);

  /**
   * @brief create entities based on input json_object
   * @param[in] json_object pointer
   * After calling this function, the entities will be created
   */
  virtual ArenaEntity* create(__unused json_object *config) = 0;

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Factory &operator=(const Factory &other) = delete;

 private:
};

NAMESPACE_END(csci3081);
#endif  // SRC_FACTORY_H_
