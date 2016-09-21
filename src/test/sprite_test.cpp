
#include <string>

#include <gtest/gtest.h>

#include "../lib/units.h"

#include "../c_sprited.h"

using std::string;
using namespace spacegun;
using aronnax::Vector2d;


TEST(Sprited, DefaultConstructor) {
  string expected = "/path/to/img.gif";
  Sprited c = Sprited(expected);
  auto actual = c.getFilePath();

  EXPECT_EQ(expected, actual);
}

TEST(Sprited, getType) {
  Sprited c = Sprited("/path");

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_SPRITED, actual);
}

TEST(Sprited, getFilePath) {
  string expected = "/path/to/img.gif";
  Sprited c = Sprited(expected);

  auto actual = c.getFilePath();

  EXPECT_EQ(expected, actual);
}
