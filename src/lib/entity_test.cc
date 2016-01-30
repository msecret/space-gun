
#include <cstdint>

#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::NiceMock;

class TestComponent : public aronnax::Component {
  public:
  void update(aronnax::Entity &entity, const uint32_t dt)
  {
    return;
  }

  std::string getType()
  {
    return "TestComponent";
  }
};

class MockComponent : public aronnax::Component {
  public:
    MOCK_METHOD2(update, void(aronnax::Entity &entity, const uint32_t dt));
    MOCK_METHOD1(render, void(aronnax::Entity &entity));
    MOCK_METHOD0(getType, std::string());
};

class TestRenderer : public aronnax::Renderer {
  public:
    TestRenderer() { };
    ~TestRenderer() { };
    void render() { };
    void beforeRender() { };
    void afterRender() { };
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
  EXPECT_EQ(0, ea_->pos.x);
  EXPECT_EQ(0, ea_->pos.y);
  EXPECT_EQ(0, ea_->box.x);
  EXPECT_EQ(0, ea_->box.y);
  EXPECT_EQ(0, ea_->v.x);
  EXPECT_EQ(0, ea_->v.y);
}


TEST_F(EntityTest, hasComponent) {
  cla_.push_back(ca_);
  ea_ = new aronnax::Entity(cla_);
  bool actual = ea_->hasComponent("TestComponent");
  EXPECT_TRUE(actual);
  actual = ea_->hasComponent("NoComponent");
  EXPECT_FALSE(actual);
}

TEST_F(EntityTest, getRenderer) {
  std::shared_ptr<TestRenderer> testRenderer = std::make_shared<TestRenderer>();
  ea_ = new aronnax::Entity(cla_, testRenderer);
  EXPECT_EQ(ea_->getRenderer(), testRenderer.get());
}

TEST_F(EntityTest, getComponent) {
  cla_.push_back(ca_);
  ea_ = new aronnax::Entity(cla_);
  auto actual = ea_->getComponent("TestComponent");
  EXPECT_EQ(actual, ca_);
}

TEST_F(EntityTest, getComponentFail) {
  ASSERT_DEATH({ ea_->getComponent("NoComponent"); }, "");
}

TEST_F(EntityTest, update) {
  const uint32_t testDt = 1;
  NiceMock<MockComponent> mockComponent;

  cla_.push_back(&mockComponent);
  ea_ = new aronnax::Entity(cla_);

  EXPECT_CALL(mockComponent, update(_, testDt)).Times(1);

  ea_->update(testDt);
}

TEST_F(EntityTest, render) {
  const uint32_t testDt = 1;
  NiceMock<MockComponent> mockComponent;

  cla_.push_back(&mockComponent);
  ea_ = new aronnax::Entity(cla_);

  EXPECT_CALL(mockComponent, render(_)).Times(1);

  ea_->render();
}
