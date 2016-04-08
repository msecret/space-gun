
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../c_mortal.h"

using spacegun::COMPONENT_TYPE_MORTAL;
using spacegun::Mortal;

TEST(Mortal, getType) {
  Mortal c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_MORTAL);
}

TEST(Mortal, addDeath) {
  Mortal c;

  auto actual = c.getDeaths();

  EXPECT_EQ(actual, 0);

  c.addDeath();
  actual = c.getDeaths();

  EXPECT_EQ(actual, 1);
}
