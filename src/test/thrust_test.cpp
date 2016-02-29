
#include <gtest/gtest.h>

#include "../c_thrustable.h"

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
