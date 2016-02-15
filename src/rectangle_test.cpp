
#include "gtest/gtest.h"

#include "lib/units.h"

#include "c_rectangular.h"
#include "s_rectange.h"

using namespace std;

TEST(Rectangle, getType) {
  spacegun::Rectangular c;
  EXPECT_EQ(spacegun::COMPONENT_TYPE_RECTANGULAR, c.getType());
}

TEST(Rectangle, Constructor) {
  double expectedW = 3;
  double expectedH = 5;
  auto c = spacegun::Rectangular(expectedW, expectedH);

  auto actualW = c.getW();
  auto actualH = c.getH();

  EXPECT_EQ(expectedW, actualW);
  EXPECT_EQ(expectedH, actualH);
}

TEST(Rectangle, getsetW) {
  double expected = 3;
  spacegun::Rectangular c;
  c.setW(expected);
  auto actual = c.getW();

  EXPECT_EQ(expected, actual);
}

TEST(Rectangle, getsetH) {
  double expected = 3;
  spacegun::Rectangular c;
  c.setH(expected);
  auto actual = c.getH();

  EXPECT_EQ(expected, actual);
}
