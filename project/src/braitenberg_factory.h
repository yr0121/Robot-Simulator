/**
 * @file arena_food_factory.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BRAITENBERG_FACTORY_H_
#define SRC_BRAITENBERG_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory.h"
#include "src/common.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /* @brief A braitenberg vehicle factory class that is responsible for producing braitenber vehicle
  *
  * A braitenberg vehicle factory is a derived class from facroty that can generate braitenberg vehicle
  * It has a create method that can create braitenberg vehicle
  */

class BraitenbergFactory : public Factory {
 public:
   /**
    * @brief BraitenbergFactory 's constructor.
    * Initialize the Braitenberg factory
    */
  BraitenbergFactory();

  /**
   * @brief create a braitenberg vehicle based on input JSON object pointer
   *
   * @param[in] config A json_object pointer
   * practically unused because it is called in arena
   * It create a default braitenberg_vehicle and call LoadFromObject to assign corresponding value
   */
  BraitenbergVehicle* create(__unused json_object *config) override;
};

NAMESPACE_END(csci3081);

#endif /* SRC_BRAITENBERG_FACTORY_H_ */
