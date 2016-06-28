

#include <gtest/gtest.h>

#include "../c_oriented.h"
#include "../c_moveable.h"

using aronnax::Vector2d;
using spacegun::Moveable;
using spacegun::Oriented;

class OrientedTest : public testing::Test {
  protected:
    virtual void SetUp() {
    }
};

Oriented setupOriented(float angle)
{
  Moveable m(Vector2d(), Vector2d(), angle);
  Oriented o(m);
}

TEST_F(OrientedTest, Constructor) {
  float expectedAngle = 32.0;
  auto testOriented = setupOriented(expectedAngle);
  EXPECT_EQ(expectedAngle, testOriented.getNormalizedAngle());
}

TEST_F(OrientedTest, getType) {
  using spacegun::COMPONENT_TYPE_ORIENTED;
  auto testOriented = setupOriented(0);
  auto actual = testOriented.getType();

  EXPECT_EQ(COMPONENT_TYPE_ORIENTED, actual);
}

