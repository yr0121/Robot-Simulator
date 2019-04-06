/**
 * @file params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 */

// graphics
#define X_DIM 1024
#define Y_DIM 768
#define TEXT_BOX_WIDTH 50
#define GUI_MENU_WIDTH 190
#define COMBO_BOX_WIDTH 150
#define GUI_MENU_GAP 10

// entity
#define DEFAULT_POSE \
  { 200, 200, 0}
#define DEFAULT_COLOR \
  { 255, 255, 255 }
#define DEFAULT_RADIUS 20

// mobile entity
#define STARTING_VELOCITY 0.0

// robot
#define ROBOT_INIT_POS \
  { 500, 500 , 0}

// braitenberg
#define B_MIN_RAD 8
#define B_MAX_RAD 14
#define BRAITENBERG_COLLISION_DELTA 1
#define BRAITENBERG_COLOR {122, 0, 25}
#define DEF_FOOD_BEHAV kLove
#define DEF_LIGHT_BEHAV kCoward
#define BRAITENBERG_SPEED_CONST .0025
#define BRAITENBERG_LOVE_AVG_SPEED 5
#define BRAITENBERG_TURNING_CONST 20
#define BRAITENBERG_VEHICLE_COUNT 1
#define BRAITENBERG_RATIO .5

// light_sensor
#define SENSOR_LIGHT_RAD 4

// food
#define FOOD_RADIUS 20
#define FOOD_COLLISION_DELTA 1
#define FOOD_INIT_POS \
  { 400, 400 }
#define FOOD_COLOR \
  { 0, 255, 0 }
#define N_FOOD 1
#define WITH_FOOD_DEFAULT true

// light
#define LIGHT_POSITION \
  { 200, 200 }
#define LIGHT_RADIUS 30
#define LIGHT_MIN_RADIUS 10
#define LIGHT_MAX_RADIUS 30
#define LIGHT_COLOR \
  { 255, 255, 255 }

#endif  // SRC_PARAMS_H_
