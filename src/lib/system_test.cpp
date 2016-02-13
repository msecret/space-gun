
#include <string>

#include "gtest/gtest.h"

#include "component.h"
#include "system.h"


TEST(System, getType) {
  aronnax::System s;
  EXPECT_EQ("base", s.getType());
}
