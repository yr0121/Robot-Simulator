
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena_entity.h"
#include "src/arena.h"
#include "src/braitenberg_factory.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/braitenberg_vehicle.h"
#include "src/behavior_enum.h"



 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BraitenbergFactoryTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    braitenberg_factory = new csci3081::BraitenbergFactory();
  }
  std::string json1="{\"type\": \"Braitenberg\", \"x\":270, \"y\":270, \"r\":15, \"theta\": 215, \"light_behavior\": \"None\", \"food_behavior\": \"Explore\" }";
  std::string json2="{\"type\": \"Braitenberg\", \"x\":120, \"y\":300, \"r\":15, \"theta\": 270, \"light_behavior\": \"Love\", \"food_behavior\": \"Aggressive\" }";
  std::string json3="{\"type\": \"Braitenberg\", \"x\":20, \"y\":30, \"r\":10, \"theta\": 100 }";
  std::string json4="{\"type\": \"Braitenberg\", \"x\":200, \"y\":200, \"r\":20, \"theta\": 0,\"light_behavior\": \"Coward\"}";
  std::string json5="{\"type\": \"Braitenberg\", \"x\":200, \"y\":200, \"r\":20, \"theta\": 0,\"food_behavior\": \"Love\"}";
  json_value *config1=new json_value();
  std::string err1=parse_json(config1,json1);
  json_value *config2=new json_value();
  std::string err2=parse_json(config2,json2);
  json_value *config3=new json_value();
  std::string err3=parse_json(config3,json3);
  json_value *config4=new json_value();
  std::string err4=parse_json(config4,json4);
  json_value *config5=new json_value();
  std::string err5=parse_json(config5,json5);
  virtual void TearDown() {
    delete braitenberg_factory;
    delete config1;
    delete config2;
    delete config3;
    delete config4;
    delete config5;
  }
  csci3081::BraitenbergFactory * braitenberg_factory;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BraitenbergFactoryTest, DefaultConstructor) {

};

TEST_F(BraitenbergFactoryTest,Create) {
  csci3081::BraitenbergVehicle *b1=braitenberg_factory->create(&config1->get<json_object>());
  EXPECT_EQ(b1->get_radius(),15)<< "BraitenbergFactoryTest FAIL: Radius did not match";
  EXPECT_EQ(b1->get_type(),csci3081::kBraitenberg)<< "BraitenbergFactoryTest FAIL: Type did not match";
  EXPECT_EQ(b1->get_pose().x,270)<< "BraitenbergFactoryTest FAIL: x position did not match";
  EXPECT_EQ(b1->get_pose().y,270)<< "BraitenbergFactoryTest FAIL: y position did not match";
  EXPECT_EQ(b1->get_pose().theta,215)<< "BraitenbergFactoryTest FAIL: theta did not match";
  EXPECT_EQ(b1->get_food_behavior(),csci3081::kExplore)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
  EXPECT_EQ(b1->get_light_behavior(),csci3081::kNone)<<"BraitenbergFactoryTest FAIL: light behavior did not match";

  csci3081::BraitenbergVehicle *b2=braitenberg_factory->create(&config2->get<json_object>());
  EXPECT_EQ(b2->get_radius(),15)<< "BraitenbergFactoryTest FAIL: Radius did not match";
  EXPECT_EQ(b2->get_type(),csci3081::kBraitenberg)<< "BraitenbergFactoryTest FAIL: Type did not match";
  EXPECT_EQ(b2->get_pose().x,120)<< "BraitenbergFactoryTest FAIL: x position did not match";
  EXPECT_EQ(b2->get_pose().y,300)<< "BraitenbergFactoryTest FAIL: y position did not match";
  EXPECT_EQ(b2->get_pose().theta,270)<< "BraitenbergFactoryTest FAIL: theta did not match";
  EXPECT_EQ(b2->get_food_behavior(),csci3081::kAggressive)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
  EXPECT_EQ(b2->get_light_behavior(),csci3081::kLove)<<"BraitenbergFactoryTest FAIL: light behavior did not match";

  csci3081::BraitenbergVehicle *b3=braitenberg_factory->create(&config3->get<json_object>());
  EXPECT_EQ(b3->get_radius(),10)<< "BraitenbergFactoryTest FAIL: Radius did not match";
  EXPECT_EQ(b3->get_type(),csci3081::kBraitenberg)<< "BraitenbergFactoryTest FAIL: Type did not match";
  EXPECT_EQ(b3->get_pose().x,20)<< "BraitenbergFactoryTest FAIL: x position did not match";
  EXPECT_EQ(b3->get_pose().y,30)<< "BraitenbergFactoryTest FAIL: y position did not match";
  EXPECT_EQ(b3->get_pose().theta,100)<< "BraitenbergFactoryTest FAIL: theta did not match";
  EXPECT_EQ(b3->get_food_behavior(),csci3081::kNone)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
  EXPECT_EQ(b3->get_light_behavior(),csci3081::kNone)<<"BraitenbergFactoryTest FAIL: light behavior did not match";

  csci3081::BraitenbergVehicle *b4=braitenberg_factory->create(&config4->get<json_object>());
  EXPECT_EQ(b4->get_radius(),20)<< "BraitenbergFactoryTest FAIL: Radius did not match";
  EXPECT_EQ(b3->get_type(),csci3081::kBraitenberg)<< "BraitenbergFactoryTest FAIL: Type did not match";
  EXPECT_EQ(b4->get_pose().x,200)<< "BraitenbergFactoryTest FAIL: x position did not match";
  EXPECT_EQ(b4->get_pose().y,200)<< "BraitenbergFactoryTest FAIL: y position did not match";
  EXPECT_EQ(b4->get_pose().theta,0)<< "BraitenbergFactoryTest FAIL: theta did not match";
  EXPECT_EQ(b4->get_food_behavior(),csci3081::kNone)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
  EXPECT_EQ(b4->get_light_behavior(),csci3081::kCoward)<<"BraitenbergFactoryTest FAIL: light behavior did not match";

  csci3081::BraitenbergVehicle *b5=braitenberg_factory->create(&config5->get<json_object>());
  EXPECT_EQ(b5->get_radius(),20)<< "BraitenbergFactoryTest FAIL: Radius did not match";
  EXPECT_EQ(b5->get_pose().x,200)<< "BraitenbergFactoryTest FAIL: x position did not match";
  EXPECT_EQ(b5->get_pose().y,200)<< "BraitenbergFactoryTest FAIL: y position did not match";
  EXPECT_EQ(b5->get_pose().theta,0)<< "BraitenbergFactoryTest FAIL: theta did not match";
  EXPECT_EQ(b5->get_light_behavior(),csci3081::kNone)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
  EXPECT_EQ(b5->get_food_behavior(),csci3081::kLove)<<"BraitenbergFactoryTest FAIL: light behavior did not match";
};
