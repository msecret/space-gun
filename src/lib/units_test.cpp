
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

TEST(EvUserMovement, getEventCode) {
  Vector2d expected = { 2, 5 };
  EvUserMovement ev = EvUserMovement(expected);

  auto actual = ev.getEventCode();

  EXPECT_EQ(actual, EV_USER_MOVEMENT);
}

TEST(EvUserRotation, Constructor) {
  float expected = -1.0f;
  EvUserRotation ev = EvUserRotation(expected);

  auto actual = ev.getDirection();

  EXPECT_EQ(actual, expected);
}

TEST(EvUserRotation, getEventCode) {
  float expected = -1.0f;
  EvUserRotation ev = EvUserRotation(expected);

  auto actual = ev.getEventCode();

  EXPECT_EQ(actual, EV_USER_ROTATION);
}

TEST(EvUserRotation, getsetDirection) {
  float expected = 1.0f;
  EvUserRotation ev = EvUserRotation(0.0f);

  ev.setDirection(expected);

  auto actual = ev.getDirection();

  EXPECT_EQ(actual, expected);
}

TEST(EvImpact, Constructor) {
  vector<float> expected;
  expected.push_back(1.0f);
  EvImpact ev(expected);

  auto actual = ev.getImpulses();

  EXPECT_EQ(actual, expected);
}

TEST(EvImpact, getEventCode) {
  vector<float> v;
  EvImpact ev(v);

  auto actual = ev.getEventCode();

  EXPECT_EQ(actual, EV_IMPACT);
}

TEST(EvImpact, getTotalImpulses) {
  vector<float> expected;
  expected.push_back(1.0f);
  expected.push_back(2.0f);
  EvImpact ev(expected);

  auto actual = ev.getTotalImpulses();

  EXPECT_FLOAT_EQ(actual, 3.0f);
}
