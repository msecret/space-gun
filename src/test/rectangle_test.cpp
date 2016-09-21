
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_rectangular.h"

using namespace spacegun;

TEST(Rectangular, getType) {
  Rectangular c;
  EXPECT_EQ(COMPONENT_TYPE_RECTANGULAR, c.getType());
}

TEST(Rectangular, Constructor) {
  float expectedW = 3;
  float expectedH = 5;
  auto c = Rectangular(expectedW, expectedH);

  auto actualW = c.getW();
  auto actualH = c.getH();

  EXPECT_EQ(expectedW, actualW);
  EXPECT_EQ(expectedH, actualH);
}

TEST(Rectangular, getsetW) {
  float expected = 3;
  Rectangular c;
  c.setW(expected);
  auto actual = c.getW();

  EXPECT_EQ(expected, actual);
}

TEST(Rectangular, getsetH) {
  float expected = 3;
  Rectangular c;
  c.setH(expected);
  auto actual = c.getH();

  EXPECT_EQ(expected, actual);
}

TEST(Rectangular, getShape) {
  Rectangular c(10, 10);

  auto shape = c.getShape();
  auto actual = shape->m_centroid;

  EXPECT_EQ(actual.x, 0);
  EXPECT_EQ(actual.y, 0);
}
