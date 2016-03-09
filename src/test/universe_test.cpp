
#include <string>

#include <gtest/gtest.h>
#include "../lib/units.h"

#include "../alias.h"
#include "../c_universal.h"

using std::string;
using aronnax::Vector2d;
using namespace spacegun;

class UniverseTest : public testing::Test {
  protected:
    virtual void SetUp()
    {
      Vector2d g = { 0, 0 };
      world_ = new World(g);
    }

    virtual void TearDown()
    {
      delete world_;
    }

  World* world_;
};

TEST_F(UniverseTest, constructor) {
  Universal u(*world_);

  auto actual = u.getWorld();

  EXPECT_EQ(actual, world_);
}

TEST_F(UniverseTest, getType) {
  Universal u(*world_);

  auto actual = u.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_UNIVERSAL);
}
