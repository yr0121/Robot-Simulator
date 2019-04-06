/**
 * @file food_factory.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food_factory.h"
#include "src/common.h"
#include "src/params.h"
#include "src/food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
FoodFactory::FoodFactory() {}
Food* FoodFactory::create(__unused json_object* config) {
  Food* food = new Food();
  food->LoadFromObject(config);
  return food;
}

NAMESPACE_END(csci3081);
