
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_shaped.h"
#include "../c_rectangular.h"

using aronnax::Entity;
using aronnax::Vector2d;
using namespace spacegun;

TEST(Shaped, getType) {
  Rectangular r;
  Shaped<Rectangular> c(r);

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_SHAPED);
}

TEST(Shaped, getShapeType) {
  Rectangular r;
  Shaped<Rectangular> c(r);

  auto actual = c.getShapeType();

  EXPECT_EQ(actual, "rectangular");
}

TEST(Shaped, getShapeComponent) {
  Rectangular r;
  Shaped<Rectangular> c(r);

  auto shaped = c.getShapeComponent();
  auto actual = shaped->getShape();

  EXPECT_EQ(actual, r.getShape());
}
