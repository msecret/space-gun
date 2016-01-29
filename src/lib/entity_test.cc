
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
  EXPECT_EQ(0, ea_->pos.x) << "Constructs with position as 0 by default";
  EXPECT_EQ(0, ea_->pos.y);
  EXPECT_EQ(0, ea_->box.x);
  EXPECT_EQ(0, ea_->box.y);
  EXPECT_EQ(0, ea_->v.x);
  EXPECT_EQ(0, ea_->v.y);
}
