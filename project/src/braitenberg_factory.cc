/**
 * @file food_factory.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/braitenberg_factory.h"
#include "src/common.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
BraitenbergFactory::BraitenbergFactory() {}
BraitenbergVehicle* BraitenbergFactory::create(__unused json_object *config) {
  BraitenbergVehicle* bv = new BraitenbergVehicle();
  bv->LoadFromObject(config);
  return bv;
}

NAMESPACE_END(csci3081);
