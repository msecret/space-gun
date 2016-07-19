
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_hideable.h"

using aronnax::Entity;

using spacegun::COMPONENT_TYPE_HIDEABLE;
using spacegun::Hideable;

TEST(Hideable, getType) {
  Hideable c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_HIDEABLE);
}

TEST(Hideable, constructor) {
  Hideable c;

  EXPECT_FALSE(c.getHidden());
}

TEST(Hideable, getsetHidden) {
  Hideable c(true);

  EXPECT_TRUE(c.getHidden());

  c.setHidden(false);

  EXPECT_FALSE(c.getHidden());
}

