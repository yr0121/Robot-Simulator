/**
 * @file controller.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_VIEWER_H_
#define SRC_ARENA_VIEWER_H_

#include "src/arena.h"

NAMESPACE_BEGIN(csci3081);

class ArenaViewer {
 public:
  virtual ~ArenaViewer() {}
  virtual bool RunViewer() = 0;
  virtual void SetArena(Arena* arena) = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_VIEWER_H_
