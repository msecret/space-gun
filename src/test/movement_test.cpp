
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_moveable.h"
#include "../s_movement.h"

using namespace aronnax;
using aronnax::Vector2d;

TEST(Movement, getType) {
  spacegun::Moveable c;
  EXPECT_EQ(spacegun::COMPONENT_TYPE_MOVEABLE, c.getType());
}

TEST(Movement, constructor) {
  Vector2d expectedVel = { 2, 3 };
  Vector2d expectedPos = { 10, 20 };
  spacegun::Moveable c = spacegun::Moveable(expectedVel, expectedPos);

  auto actualVel = c.getVel();
  auto actualPos = c.getPos();

  EXPECT_EQ(actualVel, expectedVel);
  EXPECT_EQ(actualPos, expectedPos);
}

TEST(Movement, getsetVel) {
  Vector2d expectedVel = { 2, 5 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setVel(expectedVel);
  auto actualVel = c.getVel();

  EXPECT_EQ(expectedVel.x, actualVel.x);
  EXPECT_EQ(expectedVel.y, actualVel.y);
}

TEST(Moveable, getsetPos) {
  Vector2d expectedPos = { 3, 5 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setPos(expectedPos);
  auto actual = c.getPos();

  EXPECT_EQ(expectedPos, actual);
}

TEST(Moveable, movePos) {
  Vector2d vel = { 1, 1 };
  Vector2d initPos = { 1, 1 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setPos(initPos);
  c.move(vel);
  auto actual = c.getPos();

  EXPECT_EQ(actual, initPos + vel);
}
