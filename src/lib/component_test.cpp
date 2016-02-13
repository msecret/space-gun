
#include <string>

#include "gtest/gtest.h"

#include "component.h"

TEST(Component, getType) {
  aronnax::Component c;
  EXPECT_EQ(aronnax::COMPONENT_TYPE_BASE, c.getType());
}
