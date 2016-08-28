
#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "component.h"
#include "entity.h"
#include "manager.h"
#include "system.h"

using namespace std;
using ::testing::_;
using ::testing::ByRef;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;

class MockSystem: public aronnax::System {
  public:
    MOCK_METHOD1(init, void(aronnax::Entities& entities));
    MOCK_METHOD2(update, void(const uint32_t dt, aronnax::Entities& entities));
    MOCK_METHOD2(render, void(const uint32_t dt, aronnax::Entities& entities));
    MOCK_METHOD0(getType, const std::string&());
    MOCK_METHOD1(onAddEntity, void(aronnax::Entity& entity));
};

class MockEntity: public aronnax::Entity {
  public:
    MOCK_METHOD1(hasComponent, bool(std::string componentType));
    MOCK_METHOD0(getComponentTypes, std::vector<std::string>());
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
  std::string testType = "testType";
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;
  NiceMock<MockEntity> entityA;
  NiceMock<MockEntity> entityB;

  ON_CALL(systemA, getType())
    .WillByDefault(ReturnRef(testType));
  ON_CALL(systemB, getType())
    .WillByDefault(ReturnRef("somethingelse"));

  ON_CALL(entityA, hasComponent(testType))
    .WillByDefault(Return(true));
  ON_CALL(entityB, hasComponent(testType))
    .WillByDefault(Return(false));

  testManager_->addEntity(entityA);
  testManager_->addEntity(entityB);
  testManager_->addSystem(&systemA);
  testManager_->addSystem(&systemB);

  auto actualEntityList = testManager_->getEntities(testType);

  EXPECT_CALL(systemA, update(testDt, actualEntityList)).Times(2);
  EXPECT_CALL(systemB, update(testDt, _)).Times(2);

  testManager_->update(testDt);
  testManager_->update(testDt);
}

TEST_F(ManagerTest, render) {
  const uint32_t testDt = 25;
  std::string testType = "testType";
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;
  NiceMock<MockEntity> entityA;
  NiceMock<MockEntity> entityB;

  ON_CALL(systemA, getType())
    .WillByDefault(ReturnRef(testType));
  ON_CALL(systemB, getType())
    .WillByDefault(ReturnRef("somethingelse"));

  ON_CALL(entityA, hasComponent(testType))
    .WillByDefault(Return(true));
  ON_CALL(entityB, hasComponent(testType))
    .WillByDefault(Return(false));

  testManager_->addEntity(entityA);
  testManager_->addEntity(entityB);
  testManager_->addSystem(&systemA);
  testManager_->addSystem(&systemB);

  auto actualEntityList = testManager_->getEntities(testType);

  EXPECT_CALL(systemA, render(testDt, actualEntityList)).Times(2);
  EXPECT_CALL(systemB, render(testDt, _)).Times(2);

  testManager_->render(testDt);
  testManager_->render(testDt);
  testManager_->update(testDt);
}

TEST_F(ManagerTest, addEntity) {
  std::string testType = "testType";
  NiceMock<MockSystem> testSystem;
  NiceMock<MockEntity> entity;

  std::vector<std::string> expectedComponentList; 
  expectedComponentList.push_back(testType);

  ON_CALL(testSystem, getType())
    .WillByDefault(ReturnRef(testType));
  ON_CALL(entity, getComponentTypes())
    .WillByDefault(Return(expectedComponentList));

  EXPECT_CALL(testSystem, onAddEntity(_)).Times(1);

  testManager_->addSystem(&testSystem);
  testManager_->addEntity(entity);

  auto actual = testManager_->getEntities();

  EXPECT_EQ(1, actual.size());
}

TEST_F(ManagerTest, addSystem) {
  std::string testType = "testType";
  NiceMock<MockSystem> expected;
  NiceMock<MockEntity> entity;

  ON_CALL(expected, getType())
    .WillByDefault(ReturnRef(testType));
  ON_CALL(entity, hasComponent(testType))
    .WillByDefault(Return(true));

  testManager_->addEntity(entity);

  auto expectedEntities = testManager_->getEntities(testType);
  EXPECT_CALL(expected, init(expectedEntities)).Times(1);

  testManager_->addSystem(&expected);
  auto actual = testManager_->getSystems();

  EXPECT_EQ(1, actual.size());
}

TEST_F(ManagerTest, createEntity) {
  aronnax::Entity& actual = testManager_->createEntity(testComponentList_);

  auto entities = testManager_->getEntities();

  EXPECT_EQ(1, entities.size());
  EXPECT_EQ(testComponentList_, actual.getComponents());
}

TEST_F(ManagerTest, getSystems) {
  string testTypeA = "Asystem";
  string testTypeB = "Bsystem";
  NiceMock<MockSystem> systemA;
  NiceMock<MockSystem> systemB;
  NiceMock<MockSystem> systemC;

  ON_CALL(systemA, getType())
    .WillByDefault(ReturnRef(testTypeA));
  ON_CALL(systemB, getType())
    .WillByDefault(ReturnRef(testTypeA));
  ON_CALL(systemC, getType())
    .WillByDefault(ReturnRef(testTypeB));

  testManager_->addSystem(&systemA);
  testManager_->addSystem(&systemB);
  testManager_->addSystem(&systemC);

  auto actual = testManager_->getSystems("Asystem");
  EXPECT_EQ(2, actual.size());
}

TEST_F(ManagerTest, getSystemsAll) {
  auto actual = testManager_->getSystems();
  EXPECT_EQ(0, actual.size());

  aronnax::System testSystem;
  testManager_->addSystem(&testSystem);

  actual = testManager_->getSystems();
  EXPECT_EQ(1, actual.size());
}

TEST_F(ManagerTest, getEntities) {
  string testType = "movement";
  NiceMock<MockEntity> entityA;
  NiceMock<MockEntity> entityB;

  ON_CALL(entityA, hasComponent(testType))
    .WillByDefault(Return(true));
  ON_CALL(entityB, hasComponent(testType))
    .WillByDefault(Return(false));

  testManager_->addEntity(entityA);
  testManager_->addEntity(entityB);

  auto actual = testManager_->getEntities(testType);

  EXPECT_EQ(0, actual.size());
}
