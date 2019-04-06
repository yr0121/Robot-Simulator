/**
 * @file arena_food_factory.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_FACTORY_H_
#define SRC_FOOD_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory.h"
#include "src/common.h"
#include "src/food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /* @brief A food factory class that is responsible for producing food
  *
  * A food factory is a derived class from facroty that can generate food
  * It has a create method that can create food
  */
class FoodFactory : public Factory {
 public:
   /**
    * @brief Food 's constructor.
    * Initialize the Food factory
    */
  FoodFactory();
  /**
   * @brief create food based on input JSON object pointer
   *
   * @param[in] config A json_object pointer
   * practically unused because it is called in arena
   * It create a default food and call LoadFromObject to assign corresponding value
   */
  Food* create(__unused json_object* config) override;
};

NAMESPACE_END(csci3081);
#endif  // SRC_FOOD_FACTORY_H_
