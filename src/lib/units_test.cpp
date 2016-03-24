
#include <string>

#include "units.h"
#include "gtest/gtest.h"

using namespace std;

TEST(ColorUnits, Constructor) {
  aronnax::Color ca(255, 255, 200, 0);

  EXPECT_EQ(255, ca.r);
  EXPECT_EQ(255, ca.g);
  EXPECT_EQ(200, ca.b);
  EXPECT_EQ(0, ca.a);
}

TEST(ColorUnits, EqualityOperator) {
  aronnax::Color ca(255, 255, 200, 0);
  aronnax::Color cb(255, 255, 200, 0);

  EXPECT_EQ(ca, cb);
}

TEST(ColorUnits, InequalityOperator) {
  aronnax::Color ca(255, 255, 200, 0);
  aronnax::Color cb(255, 110, 200, 0);

  EXPECT_NE(ca, cb);
}

using namespace aronnax;
TEST(Ev, Constructor) {
  Ev ev;
}

TEST(EvKeyState, Constructor) {
  string expectedKey = "A";
  EvKeyState expectedState = EvKeyState::STATE_DOWN;
  EvKeyboard ev = EvKeyboard(expectedKey, expectedState);

  EXPECT_EQ(expectedKey, ev.getKey());
  EXPECT_EQ(expectedState, ev.getKeyState());
}

TEST(EvUserMovement, Constructor) {
  Vector2d expected = { 2, 5 };
  EvUserMovement ev = EvUserMovement(expected);

  EXPECT_EQ(expected, ev.getDirection());
}

TEST(EvUserRotation, Constructor) {
  float expected = -1.0f;
  EvUserRotation ev = EvUserRotation(expected);

  auto actual = ev.getDirection();

  EXPECT_EQ(actual, expected);
}

TEST(EvUserRotation, getsetDirection) {
  float expected = 1.0f;
  EvUserRotation ev = EvUserRotation(0.0f);

  ev.setDirection(expected);

  auto actual = ev.getDirection();

  EXPECT_EQ(actual, expected);
}
