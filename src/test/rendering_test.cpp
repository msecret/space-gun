
#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_rendered.h"

using std::string;
using aronnax::Vector2d;
using namespace spacegun;

TEST(Rendered, constructor) {
  Rendered c;

  auto actual = c.getTexture();

  EXPECT_EQ(actual, nullptr);
}

TEST(Rendered, getType) {
  Rendered c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_RENDERED);
}

TEST(Rendered, getsetSurface) {
  Rendered c;

  auto actual = c.getSurface();

  EXPECT_EQ(actual, nullptr);

}
