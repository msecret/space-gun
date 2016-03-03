
#include <string>

#include "units.h"
#include "gtest/gtest.h"

using namespace std;

TEST(VectorUnits, DefaultConstructor) {
  const aronnax::Vector2d va;
  EXPECT_EQ(0, va.x);
  EXPECT_EQ(0, va.y);
}

TEST(VectorUnits, AdditionOperator) {
  const aronnax::Vector2d va(5, 3);
  const aronnax::Vector2d vb(1, 3);
  aronnax::Vector2d vc = va + vb;
  EXPECT_EQ(6, vc.x);
  EXPECT_EQ(6, vc.y);
}

TEST(VectorUnits, SubtractionOperator) {
  aronnax::Vector2d va(1, 2);
  aronnax::Vector2d vb(1, 1);
  aronnax::Vector2d expected(0, 1);

  auto actual = va - vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(VectorUnits, MultiplicationOperator) {
  aronnax::Vector2d va(1, 2);
  aronnax::Vector2d vb(3, 2);
  aronnax::Vector2d expected(3, 4);

  auto actual = va * vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(VectorUnits, DivisionOperator) {
  aronnax::Vector2d va(10, 6);
  aronnax::Vector2d vb(2, 3);
  aronnax::Vector2d expected(5, 2);

  auto actual = va / vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(VectorUnits, AdditionAssignmentOperator) {
  aronnax::Vector2d va(5, 3);
  aronnax::Vector2d vb(1, 3);

  va += vb;
  EXPECT_EQ(6, va.x);
  EXPECT_EQ(6, va.y);
}

TEST(VectorUnits, EqualityOperator) {
  aronnax::Vector2d va(2, 3);
  aronnax::Vector2d vb(2, 3);

  EXPECT_EQ(va, vb);
}


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
