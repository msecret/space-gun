
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_moveable.h"
#include "../s_movement.h";

TEST(Movement, getType) {
  spacegun::Moveable c;
  EXPECT_EQ(spacegun::COMPONENT_TYPE_MOVEABLE, c.getType());
}

TEST(Movement, constructor) {
  aronnax::Vector2d testV = { 10, 3 };
  spacegun::Moveable c = spacegun::Moveable(testV);
}

TEST(Movement, getsetVel) {
  aronnax::Vector2d expectedVel = { 2, 5 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setVel(expectedVel);
  auto actualVel = c.getVel();

  EXPECT_EQ(expectedVel.x, actualVel.x);
  EXPECT_EQ(expectedVel.y, actualVel.y);
}
