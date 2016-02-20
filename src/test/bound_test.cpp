

#include <gtest/gtest.h>

#include "../c_boundable.h"

class BoundTest : public testing::Test {
  protected:
    virtual void SetUp() {
      testBounds_.x = 5;
      testBounds_.y = 3;
      testBoundable_ = spacegun::Boundable(testBounds_);
    }

    spacegun::Boundable testBoundable_;
    aronnax::Vector2d testBounds_;
};

TEST_F(BoundTest, Constructor) {
  auto actual = testBoundable_.getBounds();
  EXPECT_EQ(testBounds_, actual); 
}

TEST_F(BoundTest, getType) {
  auto actual = testBoundable_.getType();
  EXPECT_EQ(spacegun::COMPONENT_TYPE_BOUNDABLE, actual);
}

TEST_F(BoundTest, getBounds) {
  auto actual = testBoundable_.getBounds();
  EXPECT_EQ(testBounds_, actual); 
}
