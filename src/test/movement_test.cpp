
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_moveable.h"
#include "../s_movement.h"

using aronnax::Vector2d;
using namespace spacegun;

TEST(Moveable, init) {
  Vector2d g = { 0, 0 };
  World w(g);
  Moveable c;

  c.init(w);

  auto actual = c.getBody();

  EXPECT_NE(actual, nullptr);
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

TEST(Moveable, getsetFriction) {
  float expected = 8.2;
  spacegun::Moveable c = spacegun::Moveable();

  c.setFriction(expected);

  auto actual = c.getFriction();

  EXPECT_EQ(actual, expected);
}

TEST(Moveable, getsetRestitution) {
  float expected = 8.3;
  spacegun::Moveable c = spacegun::Moveable();

  c.setRestitution(expected);

  auto actual = c.getRestitution();

  EXPECT_EQ(actual, expected);
}

TEST(Moveable, getsetDensity) {
  float expected = 8.4;
  spacegun::Moveable c = spacegun::Moveable();

  c.setDensity(expected);
}

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
