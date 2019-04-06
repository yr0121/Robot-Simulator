/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <fstream>
#include <streambuf>

#include "src/common.h"
#include "src/controller.h"
#include "src/graphics_arena_viewer.h"
#include "src/light.h"
#include "src/food.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller(int argc, char **argv) :
  last_dt(0), viewers_(), config_(NULL) {
  if (argc > 1) {
    std::ifstream t(std::string(argv[1]).c_str());
    std::string str((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
    std::string json = str;
    config_ = new json_value();
    std::string err = parse_json(config_, json);
    if (!err.empty()) {
      std::cerr << "Parse error: " << err << std::endl;
      delete config_;
      config_ = NULL;
    } else {
      arena_ = new Arena(&config_->get<json_object>());
    }
  }
  if (!config_) {
    arena_ = new Arena();
  }
}

Controller::~Controller() {
  if (config_) {
    delete config_;
  }
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    delete viewers_[f];
  }
}

ArenaViewer* Controller::CreateViewer(int width, int height) {
  return new GraphicsArenaViewer(width, height, this);
}

void Controller::Run() {
  viewers_.push_back(CreateViewer(arena_->get_x_dim(), arena_->get_y_dim()));
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewers_[f]->SetArena(arena_);
  }

  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewer_ = viewers_[f];
    if (viewer_->RunViewer()) {
      break;
    }
  }
}

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}


void Controller::Reset() {
  Light::count = 0;
  Food::count = 0;
  BraitenbergVehicle::count = 0;

  if (arena_) {
    delete (arena_);
  }
  if (config_) {
    arena_ = new Arena(&config_->get<json_object>());
  } else {
    arena_ = new Arena();
  }
  viewer_->SetArena(arena_);
}


NAMESPACE_END(csci3081);
