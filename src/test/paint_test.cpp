
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_painted.h"

using namespace spacegun;
using aronnax::Vector2d;

TEST(Painted, DefaultConstructor) {
  aronnax::Color expected;
  Painted c = Painted();
  auto actual = c.getColor();

  EXPECT_EQ(expected, actual);
}

TEST(Painted, ColorConstructor) {
  aronnax::Color expected = { 155, 155, 255, 155 };
  Painted c = Painted(expected);

  auto  actual = c.getColor();

  EXPECT_EQ(expected, actual);
}

TEST(Painted, RGBAConstructor) {
  aronnax::Color e = { 234, 155, 0, 255 };
  Painted c = Painted(e.r, e.g, e.b, e.a);

  auto  actual = c.getColor();

  EXPECT_EQ(e, actual);
}

TEST(Painted, getType) {
  Painted c = Painted();

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_PAINTED, actual);
}

TEST(Painted, getsetColor) {
  aronnax::Color expected = { 155, 155, 255, 155 };
  Painted c = Painted();

  c.setColor(expected);
  auto actual = c.getColor();

  EXPECT_EQ(expected, actual);
}
