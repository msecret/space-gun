
#include "units.h"
#include "gtest/gtest.h"

TEST(Units, DefaultConstructor) {
  const aronnax::Vector2d va;
  EXPECT_EQ(0, va.x);
  EXPECT_EQ(0, va.y);
}
