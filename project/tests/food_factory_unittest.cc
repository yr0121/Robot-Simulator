
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena_entity.h"
#include "src/food_factory.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/food.h"
#include "src/behavior_enum.h"
#include "src/params.h"



 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FoodFactoryTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    food_factory = new csci3081::FoodFactory();
  }
  virtual void TearDown() {
    delete food_factory;
    delete config1;
    delete config2;
    delete config3;
  }
  std::string json1="{\"type\": \"Food\", \"x\":200, \"y\":200, \"r\":20, \"theta\": 0.0}";
  json_value *config1=new json_value();
  std::string err1=parse_json(config1,json1);

  std::string json2="{\"type\": \"Food\", \"x\":0, \"y\":0, \"r\":1, \"theta\": 10.0}";
  json_value *config2=new json_value();
  std::string err2=parse_json(config2,json2);

  std::string json3="{\"type\": \"Food\", \"x\":200,\"y\":20, \"r\":31}";
  json_value *config3=new json_value();
  std::string err3=parse_json(config3,json3);

  csci3081::FoodFactory * food_factory;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FoodFactoryTest, Constructor) {

};

TEST_F(FoodFactoryTest,Create) {
  csci3081::Food *f1=food_factory->create(&config1->get<json_object>());
  EXPECT_EQ(f1->get_type(),csci3081::kFood)<<"FoodFactoryTest FAIL:type did not match";
  EXPECT_EQ(f1->get_radius(),20)<<"FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f1->get_pose().x,200)<< "FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f1->get_pose().y,200)<< "FoodFactoryTest FAIL: y position did not match";
  EXPECT_EQ(f1->get_pose().theta,0.0)<< "FoodFactoryTest FAIL: theta did not match";

  csci3081::Food *f2=food_factory->create(&config2->get<json_object>());
  EXPECT_EQ(f2->get_type(),csci3081::kFood)<<"FoodFactoryTest FAIL:type did not match";
  EXPECT_EQ(f2->get_radius(),1)<<"FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f2->get_pose().x,0)<< "FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f2->get_pose().y,0)<< "FoodFactoryTest FAIL: y position did not match";
  EXPECT_EQ(f2->get_pose().theta,10.0)<< "FoodFactoryTest FAIL: theta did not match";

  csci3081::Food *f3=food_factory->create(&config3->get<json_object>());
  EXPECT_EQ(f3->get_type(),csci3081::kFood)<<"FoodFactoryTest FAIL:type did not match";
  EXPECT_EQ(f3->get_radius(),31)<<"FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f3->get_pose().x,200)<< "FoodFactoryTest FAIL: x position did not match";
  EXPECT_EQ(f3->get_pose().y,20)<< "FoodFactoryTest FAIL: y position did not match";
  EXPECT_EQ(f3->get_pose().theta,0.0)<< "FoodFactoryTest FAIL: theta did not match";

};
