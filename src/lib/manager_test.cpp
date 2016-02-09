
#include <cstdint>
#include <string>

#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "manager.h"
#include "system.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

class MockSystem: public aronnax::System {
  public:
    MOCK_METHOD1(update, void(const uint32_t dt));
    MOCK_METHOD1(render, void(const uint32_t dt));
    MOCK_METHOD0(getType, std::string());
};

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
  const uint32_t testDt = 20;
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;

  testManager_->addSystem(systemA);
  testManager_->addSystem(systemB);

  EXPECT_CALL(systemA, update(testDt)).Times(2);
  EXPECT_CALL(systemB, update(testDt)).Times(2);

  testManager_->update(testDt);
  testManager_->update(testDt);
}

TEST_F(ManagerTest, render) {
  const uint32_t testDt = 25;
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;

  testManager_->addSystem(systemA);
  testManager_->addSystem(systemB);

  EXPECT_CALL(systemA, render(testDt)).Times(2);
  EXPECT_CALL(systemB, render(testDt)).Times(2);

  testManager_->render(testDt);
  testManager_->render(testDt);
  testManager_->update(testDt);
}

TEST_F(ManagerTest, addEntity) {
  auto e = new aronnax::Entity(testComponentList_);

  testManager_->addEntity(*e);

  auto actual = testManager_->getEntities();

  EXPECT_EQ(1, actual.size());
  EXPECT_EQ(1, actual.count(e));
}

TEST_F(ManagerTest, addSystem) {
  aronnax::System expected;

  testManager_->addSystem(expected);
  auto actual = testManager_->getSystems();

  EXPECT_EQ(1, actual.size());
}

TEST_F(ManagerTest, createEntity) {
  aronnax::IEntity& actual = testManager_->createEntity(testComponentList_);

  auto entities = testManager_->getEntities();

  EXPECT_EQ(1, entities.size());
  EXPECT_EQ(1, entities.count(&actual));
  EXPECT_EQ(testComponentList_, actual.getComponents());
}

TEST_F(ManagerTest, getSystems) {
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;
  NiceMock<MockSystem> systemC;

  ON_CALL(systemA, getType())
    .WillByDefault(Return("Asystem"));
  ON_CALL(systemB, getType())
    .WillByDefault(Return("Asystem"));
  ON_CALL(systemC, getType())
    .WillByDefault(Return("Csystem"));

  testManager_->addSystem(systemA);
  testManager_->addSystem(systemB);
  testManager_->addSystem(systemC);

  auto actual = testManager_->getSystems("Asystem");
  EXPECT_EQ(2, actual.size());
}

TEST_F(ManagerTest, getSystemsAll) {
  auto actual = testManager_->getSystems();
  EXPECT_EQ(0, actual.size());

  aronnax::System testSystem;
  testManager_->addSystem(testSystem);

  actual = testManager_->getSystems();
  EXPECT_EQ(1, actual.size());
}

