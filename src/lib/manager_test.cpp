
#include <cstdint>

#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "manager.h"

class ManagerTest: public testing::Test {
  protected:
    virtual void SetUp() {
      testManager_ = new aronnax::Manager();
    }

    virtual void TearDown() {
      delete testManager_;
    }

    aronnax::Manager* testManager_;
    aronnax::Components testComponentList_;
};

TEST_F(ManagerTest, update) {

}

TEST_F(ManagerTest, render) {

}

TEST_F(ManagerTest, addEntity) {
  auto e = new aronnax::Entity(testComponentList_);

  testManager_->addEntity(*e);

  auto actual = testManager_->getEntities();

  EXPECT_EQ(1, actual.size());
  EXPECT_EQ(1, actual.count(e));
}

TEST_F(ManagerTest, createEntity) {
  aronnax::IEntity& actual = testManager_->createEntity(testComponentList_);

  auto entities = testManager_->getEntities();

  EXPECT_EQ(1, entities.size());
  EXPECT_EQ(1, entities.count(&actual));
  EXPECT_EQ(testComponentList_, actual.getComponents());
}

