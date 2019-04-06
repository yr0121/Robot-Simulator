/**
 * @file behavior_enum.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BEHAVIOR_ENUM_H_
#define SRC_BEHAVIOR_ENUM_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/common.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Enumeration
 ******************************************************************************/
/**
 * @brief Enumeration representing the 4 possible behaviors
 *
 */

enum Behavior {
  kNone = 0,
  kAggressive,
  kCoward,
  kExplore,
  kLove
};

inline Behavior get_behavior_type(const std::string& type) {
  if (type == "Aggressive") {
    return kAggressive;
  }
  if (type == "Love") {
    return kLove;
  }
  if (type == "Coward") {
    return kCoward;
  }
  if (type == "Explore") {
    return kExplore;
  }
  return kNone;
}

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_ENUM_H_
