/**
 * @file light_factory.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light_factory.h"
#include "src/common.h"
#include "src/params.h"
#include "src/light.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
LightFactory::LightFactory() {}
Light* LightFactory::create(__unused json_object* config) {
  Light* light = new Light();
  light->LoadFromObject(config);
  return light;
}

NAMESPACE_END(csci3081);
