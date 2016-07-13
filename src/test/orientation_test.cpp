

#include <gtest/gtest.h>

#include "../c_oriented.h"
#include "../c_moveable.h"

using aronnax::Vector2d;
using spacegun::Moveable;
using spacegun::Oriented;

class OrientedTest : public testing::Test {
  protected:
    virtual void SetUp() {
      expectedAngle_ = 15.0;
      moveable_ = new Moveable(Vector2d(), Vector2d(), expectedAngle_);
      oriented_ = new Oriented(*moveable_);
    }

    virtual void TearDown() {
      delete oriented_;
      delete moveable_;
    }

  Oriented* oriented_;
  Moveable* moveable_;
  float expectedAngle_;
};

#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

TEST_F(OrientedTest, Constructor) {
  auto expected = 139.43671;
  EXPECT_FLOAT_EQ(expected, oriented_->getNormalizedAngle());
}

TEST_F(OrientedTest, getType) {
  using spacegun::COMPONENT_TYPE_ORIENTED;
  auto actual = oriented_->getType();

  EXPECT_EQ(COMPONENT_TYPE_ORIENTED, actual);
}

TEST_F(OrientedTest, facingNorth) {
  auto actual = oriented_->facingNorth();
  EXPECT_FALSE(actual);
}
