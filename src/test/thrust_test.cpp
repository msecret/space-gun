
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

  double expected = 3;
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
  double expected = 43.2;

  c.setFactor(expected);

  auto actual = c.getFactor();

  EXPECT_EQ(expected, actual);
}

TEST(Thrust, getType) {
  Thrustable c;

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_THRUSTABLE, actual);
}

TEST(Thrust, onAddEntity) {
  Vector2d initV = { 1.5, 0 };
  Vector2d direction = { 0, -1 };
  Vector2d expected = { 1.5, -0.5 };
  double factor = 0.5;
  EvUserMovement ev(direction);

  Moveable cm(initV);
  Thrustable ct(factor);
  Entity* e = new Entity();
  Thrust s;

  e->addComponent(&cm);
  e->addComponent(&ct);

  s.onAddEntity(*e);

  e->emit(EV_USER_MOVEMENT, &ev);

  auto actual = cm.getVel();

  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
  EXPECT_EQ(expected, actual);
}
