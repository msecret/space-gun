
#include <cstdint>
#include <string>
#include <vector>

#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

class TestComponent : public aronnax::Component {
  public:
    void update(aronnax::Entity &entity, const uint32_t dt)
    {
      return;
    }
    Vector2d getVel()
    {
      Vector2d vel = { 10, 10 };
      return vel;
    }

    const std::string getType()
    {
      return "TestComponent";
    }
};

class MockComponent : public aronnax::Component {
  public:
    MOCK_METHOD2(update, void(aronnax::Entity &entity, const uint32_t dt));
    MOCK_METHOD1(render, void(aronnax::Entity &entity));
    MOCK_METHOD0(getType, const std::string());
};

class EntityTest : public testing::Test {
  protected:
  virtual void SetUp() {
    ea_ = new aronnax::Entity(cla_);
    ca_ = new TestComponent();
  }

  virtual void TearDown() {
    delete ea_;
    delete ca_;
  }

  // Declares the variables your tests want to use.
  aronnax::Components cla_;
  aronnax::Entity* ea_;
  TestComponent* ca_;
};

TEST_F(EntityTest, DefaultConstructor) {
}

TEST_F(EntityTest, hasComponent) {
  cla_.push_back(ca_);
  ea_ = new aronnax::Entity(cla_);
  bool actual = ea_->hasComponent("TestComponent");
  EXPECT_TRUE(actual);
  actual = ea_->hasComponent("NoComponent");
  EXPECT_FALSE(actual);
}

TEST_F(EntityTest, addComponent) {
  TestComponent* expected = new TestComponent();

  ea_->addComponent(expected);

  auto actual = ea_->getComponent<TestComponent>(expected->getType());

  EXPECT_EQ(expected, actual);
}

TEST_F(EntityTest, getComponent) {
  cla_.push_back(ca_);
  ea_ = new aronnax::Entity(cla_);
  auto actual = ea_->getComponent<TestComponent>("TestComponent");
  EXPECT_EQ(actual, ca_);
}

TEST_F(EntityTest, getComponentFail) {
  ASSERT_DEATH({ ea_->getComponent<TestComponent>("NoComponent"); }, "");
}

TEST_F(EntityTest, getComponents) {
  aronnax::Components expected;
  expected.push_back(ca_);
  aronnax::Entity* testEntity = new aronnax::Entity(expected);

  auto actual = testEntity->getComponents();

  EXPECT_EQ(actual, expected);
}

TEST_F(EntityTest, getComponentTypes) {
  cla_.push_back(ca_);
  ea_ = new aronnax::Entity(cla_);

  std::vector<std::string> expected;
  expected.push_back(ca_->getType());

  auto actual = ea_->getComponentTypes();

  EXPECT_EQ(actual, expected);
}
