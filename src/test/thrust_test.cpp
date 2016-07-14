
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_thrustable.h"
#include "../c_moveable.h"
#include "../s_thrust.h"

using namespace std;
using namespace aronnax;
using namespace spacegun;

TEST(Thrustable, Constructor) {
  Thrustable c;

  auto actual = c.getFactor();

  EXPECT_EQ(0, actual);

  float expected = 3;
  Thrustable ca(expected);

  actual = ca.getFactor();

  EXPECT_EQ(expected, actual);
}

TEST(Thrustable, getType) {
  Thrustable c;

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_THRUSTABLE, actual);
}

TEST(Thrustable, getsetFactor) {
  Thrustable c;
  float expected = 43.2;

  c.setFactor(expected);

  auto actual = c.getFactor();

  EXPECT_EQ(expected, actual);
}

TEST(Thrustable, getsetUpDownFactor) {
  float expectedUp = 3.4f;
  float expectedDown = 2.4f;
  float expectedRight = 1.5f;
  float expectedLeft = 5.5f;

  Thrustable c(1.0f);

  c.setUpFactor(expectedUp);
  c.setDownFactor(expectedDown);
  c.setRightFactor(expectedRight);
  c.setLeftFactor(expectedLeft);
  auto actualUp = c.getUpFactor();
  auto actualDown = c.getDownFactor();
  auto actualRight = c.getRightFactor();
  auto actualLeft = c.getLeftFactor();

  EXPECT_EQ(actualUp, expectedUp);
  EXPECT_EQ(actualDown, expectedDown);
  EXPECT_EQ(actualRight, expectedRight);
  EXPECT_EQ(actualLeft, expectedLeft);
}

TEST(Thrustable, isOrientedStrafe) {
  Thrustable ca;

  EXPECT_TRUE(ca.isOrientedStrafe());

  Thrustable cb(1.0, false);

  EXPECT_FALSE(cb.isOrientedStrafe());
}

TEST(Thrust, getType) {
  Thrustable c;

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_THRUSTABLE, actual);
}

TEST(Thrust, onAddEntity) {
  Vector2d g = { 0.0, 0.0 };
  Vector2d initP = { 0, 0 };
  Vector2d initV = { 0, 0 };
  Vector2d direction = { 1, 1 };
  float factor = 1000;
  EvUserMovement ev(direction);
  World w(g);
  PolygonShape p;
  p.SetAsBox(2, 1);

  Moveable cm(initP, initV);
  Thrustable ct(factor);
  Entity* e = new Entity();
  Thrust s;
  cm.init(w, p);

  e->addComponent(&cm);
  e->addComponent(&ct);

  s.onAddEntity(*e);

  e->emit(EV_USER_MOVEMENT, &ev);
  w.Step(0.8, 8, 2);

  auto actual = cm.getVel();

  EXPECT_FLOAT_EQ(actual.x, 2.5);
  EXPECT_FLOAT_EQ(actual.y, 0.0);
}
