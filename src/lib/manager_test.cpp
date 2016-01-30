
#include <cstdint>

#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "manager.h"

using ::testing::Mock;
using ::testing::NiceMock;
using ::testing::Return;

// TODO move to shared testing file
class TestRenderer : public aronnax::Renderer {
  public:
    TestRenderer() { };
    ~TestRenderer() { };
    void render() { };
    void beforeRender() { };
    void afterRender() { };
};

class MockRenderer: public TestRenderer {
  public:
    MOCK_METHOD0(render, void());
    MOCK_METHOD0(beforeRender, void());
    MOCK_METHOD0(afterRender, void());
};

// TODO move to shared testing file
class MockComponent : public aronnax::Component {
  public:
    MOCK_METHOD2(update, void(aronnax::Entity &entity, const uint32_t dt));
    MOCK_METHOD1(render, void(aronnax::Entity &entity));
    MOCK_METHOD0(getType, std::string());
};


class ManagerTest: public testing::Test {
  protected:
    virtual void SetUp() {
      std::shared_ptr<TestRenderer> tr = std::make_shared<TestRenderer>();
      testManager_ = new aronnax::Manager(tr, testEntities_);
    }

    virtual void TearDown() {
      delete testManager_;
    }

    aronnax::Manager* testManager_;
    aronnax::Entities testEntities_;
    aronnax::Components testComponentList_;
};

TEST(manager, Constructor) {
  std::shared_ptr<TestRenderer> testRenderer = std::make_shared<TestRenderer>();
  aronnax::Manager testManager(testRenderer);
}

TEST_F(ManagerTest, add) {
  NiceMock<MockComponent> testComponent;
  testComponentList_.push_back(&testComponent);

  ON_CALL(testComponent, getType())
      .WillByDefault(Return("TestComponentA"));

  auto actual = testManager_->add(testComponentList_);
  EXPECT_EQ(1, testManager_->getEntities().size());
  EXPECT_EQ(1, testManager_->getEntities().count(actual));

  auto actualComponent = actual.get()->getComponent("TestComponentA");
  EXPECT_EQ(actualComponent, &testComponent);

  actual = testManager_->add(testComponentList_);
  EXPECT_EQ(2, testManager_->getEntities().size());
  EXPECT_EQ(1, testManager_->getEntities().count(actual));
}

TEST_F(ManagerTest, getEntities) {
  aronnax::EntityPtr testEntity = std::make_shared<aronnax::Entity>(
      testComponentList_);
  testEntities_.insert(testEntity);

  std::shared_ptr<TestRenderer> tr = std::make_shared<TestRenderer>();
  auto testManager = new aronnax::Manager(tr, testEntities_);

  auto actual = testManager_->getEntities().size();
  //EXPECT_EQ(1, actual);
}

TEST_F(ManagerTest, render) {
  std::shared_ptr<MockRenderer> mockRenderer = std::make_shared<MockRenderer>();
  auto* testManager = new aronnax::Manager(mockRenderer, testEntities_);

  EXPECT_CALL(*mockRenderer, beforeRender()).Times(1);
  EXPECT_CALL(*mockRenderer, afterRender()).Times(1);

  testManager->render();
  Mock::AllowLeak(mockRenderer.get());
  Mock::VerifyAndClearExpectations(mockRenderer.get());
}
