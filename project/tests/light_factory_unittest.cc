
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena_entity.h"
#include "src/light_factory.h"
#include "src/entity_type.h"



 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class LightFactoryTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    light_factory = new csci3081::LightFactory();
  }
  virtual void TearDown() {
    delete light_factory;
    delete config1;
    delete config2;
    delete config3;
  }
  std::string json1="{\"type\": \"Light\", \"x\":150, \"y\":300, \"r\":25}";
  json_value *config1=new json_value();
  std::string err1=parse_json(config1,json1);

  std::string json2="{\"type\": \"Light\", \"x\":10, \"y\":30, \"r\":0.01}";
  json_value *config2=new json_value();
  std::string err2=parse_json(config2,json2);

  std::string json3="{\"type\": \"Light\", \"x\":150, \"y\":300, \"r\":25,\"theta\":45}";
  json_value *config3=new json_value();
  std::string err=parse_json(config3,json3);
  csci3081::LightFactory * light_factory;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LightFactoryTest, Constructor) {

};

TEST_F(LightFactoryTest,Create) {
  csci3081::Light *l1=light_factory->create(&config1->get<json_object>());
  EXPECT_EQ(l1->get_type(),csci3081::kLight)<<"LightFactoryTest FAIL:type did not match";
  EXPECT_EQ(l1->get_radius(),25)<<"LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l1->get_pose().x,150)<< "LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l1->get_pose().y,300)<< "LightFactoryTest FAIL: y position did not match";

  csci3081::Light *l2=light_factory->create(&config2->get<json_object>());
  EXPECT_EQ(l2->get_type(),csci3081::kLight)<<"LightFactoryTest FAIL:type did not match";
  EXPECT_EQ(l2->get_radius(),0.01)<<"LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l2->get_pose().x,10)<< "LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l2->get_pose().y,30)<< "LightFactoryTest FAIL: y position did not match";

  csci3081::Light *l3=light_factory->create(&config3->get<json_object>());
  EXPECT_EQ(l3->get_type(),csci3081::kLight)<<"LightFactoryTest FAIL:type did not match";
  EXPECT_EQ(l3->get_radius(),25)<<"LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l3->get_pose().x,150)<< "LightFactoryTest FAIL: x position did not match";
  EXPECT_EQ(l3->get_pose().y,300)<< "LightFactoryTest FAIL: y position did not match";
  EXPECT_EQ(l3->get_pose().theta,45)<< "LightFactoryTest FAIL: y position did not match";

};
