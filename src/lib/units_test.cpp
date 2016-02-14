
#include "units.h"
#include "gtest/gtest.h"

TEST(Units, DefaultConstructor) {
  const aronnax::Vector2d va;
  EXPECT_EQ(0, va.x);
  EXPECT_EQ(0, va.y);
}

TEST(Units, AdditionOperator) {
  const aronnax::Vector2d va(5, 3);
  const aronnax::Vector2d vb(1, 3);
  aronnax::Vector2d vc = va + vb;
  EXPECT_EQ(6, vc.x);
  EXPECT_EQ(6, vc.y);
}

TEST(Units, SubtractionOperator) {
  aronnax::Vector2d va(1, 2);
  aronnax::Vector2d vb(1, 1);
  aronnax::Vector2d expected(0, 1);

  auto actual = va - vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(Units, MultiplicationOperator) {
  aronnax::Vector2d va(1, 2);
  aronnax::Vector2d vb(3, 2);
  aronnax::Vector2d expected(3, 4);

  auto actual = va * vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(Units, DivisionOperator) {
  aronnax::Vector2d va(10, 6);
  aronnax::Vector2d vb(2, 3);
  aronnax::Vector2d expected(5, 2);

  auto actual = va / vb;
  EXPECT_EQ(expected.x, actual.x);
  EXPECT_EQ(expected.y, actual.y);
}

TEST(Units, AdditionAssignmentOperator) {
  aronnax::Vector2d va(5, 3);
  aronnax::Vector2d vb(1, 3);

  va += vb;
  EXPECT_EQ(6, va.x);
  EXPECT_EQ(6, va.y);
}

TEST(Units, EqualityOperator) {
  aronnax::Vector2d va(2, 3);
  aronnax::Vector2d vb(2, 3);

  EXPECT_EQ(va, vb);
}

