
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

class EntityTest : public testing::Test {
protected:

  virtual void SetUp() {
  }

  // Declares the variables your tests want to use.
  aronnax::Components cla_;
  aronnax::Entity ea_;
};
*/

TEST(Entity, DefaultConstructor) {
  const aronnax::Components cla_;
  const aronnax::Entity ea_(cla_);
  EXPECT_EQ(0, ea_.pos.x) << "Constructs with position as 0 by default";
  EXPECT_EQ(0, ea_.pos.y);
  EXPECT_EQ(0, ea_.box.x);
  EXPECT_EQ(0, ea_.box.y);
}
