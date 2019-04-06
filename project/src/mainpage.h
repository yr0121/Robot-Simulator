/*!
 @copyright 2017 3081 Staff and Yuanhao Ruan, All rights reserved.
 \mainpage CSCI 3081 Project
 *
 * \section intro_sec Introduction
 *
 * This is the main page for iteration1.
 *
 * In this iteration, the program simulates braitenberg vehicle(robot) interaction with food and light.
 * The robot, light and food could exists in different scenes which are specifies by different JSON object.
 * Food are immobile entites and light and robot could  move around the arena.
 * In addition to default behavior (No movement), the food and light could exhibit four different behaviors:
 * love, coward, aggressive and explore that enables robot to move toward or away from them.
 * The robot has food and light sensors that detect the food and light. The sensors also have readings that are used in change wheel velocity.
 * The robot has a left wheel and a right wheel which are responsible for turning direction and change velocity of the whole robot.
 * When the robot and food or light appear in a reasonable distance, the velocity of robot will change based on behaviors.
 * If the robot collide with the wall, it will turn 180 degrees, adjust its left anf right wheel velocity, move 30 timesteps
 * and turn 45 degrees to handle the collision.
 * The robot color will also change according to which sensors are driving the robot.
 * When food and light sensors both working, the robot color will change to maroon.
 * When food and light sensors not working, the robot color will change to maroon as well.
 * When only food sensor works, the robot will change color to blue.
 * When only light sensor works, the robot will change color to gold.
 *
 * A factory design has been implemented to enable the production of food, light and robot.
 * An abstract base class is created and three derived class inherit from the base class.
 * Instead of creating objects directly in arena, now the arena calls different factories to produce corresponding
 * entities.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
#endif  // SRC_MAINPAGE_H_
