/**
 * @file entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/common.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum EntityType {
  kLight = 0, kFood, kEntity, kBraitenberg,
  kRightWall, kLeftWall, kTopWall, kBottomWall,
  kUndefined
};

inline EntityType get_entity_type(const std::string& type) {
  if (type == "Light") {
    return kLight;
  }
  if (type == "Food") {
    return kFood;
  }
  if (type == "Braitenberg") {
    return kBraitenberg;
  }
  return kUndefined;
}

NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_TYPE_H_
