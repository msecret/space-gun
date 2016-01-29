
#include "component.h"
#include "entity.h"
#include "gtest/gtest.h"

/*
class TestC : public aronnax::Component {
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
*/

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
  }

  // Declares the variables your tests want to use.
  aronnax::Components cla_;
  aronnax::Entity* ea_;
};

TEST_F(EntityTest, DefaultConstructor) {
  EXPECT_EQ(0, ea_->pos.x);
  EXPECT_EQ(0, ea_->pos.y);
  EXPECT_EQ(0, ea_->box.x);
  EXPECT_EQ(0, ea_->box.y);
  EXPECT_EQ(0, ea_->v.x);
  EXPECT_EQ(0, ea_->v.y);
}

TEST_F(EntityTest, RendererConstructor) {
  std::shared_ptr<TestRenderer> testRenderer = std::make_shared<TestRenderer>();
  aronnax::Entity* ea = new aronnax::Entity(cla_, testRenderer);
  EXPECT_EQ(ea->getRenderer(), testRenderer.get());
}
