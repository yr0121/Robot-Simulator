/**
 * @file arena_light_factory.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_FACTORY_H_
#define SRC_LIGHT_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/factory.h"
#include "src/common.h"
#include "src/light.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /* @brief A Light factory class that is responsible for producing light
  *
  * A light factory is a derived class from facroty that can generate light
  * It has a create method that can create light
  */
class LightFactory : public Factory {
 public:
  /**
    * @brief light's constructor.
    * Initialize the light factory
  */
  LightFactory();
  /**
   * @brief create a light based on input JSON object pointer
   *
   * @param[in] config A json_object pointer
   * practically unused because it is called in arena
   * It create a default food and call LoadFromObject to assign corresponding value
   */
  Light* create(__unused json_object *config) override;
};

NAMESPACE_END(csci3081);
#endif  // SRC_LIGHT_FACTORY_H_
