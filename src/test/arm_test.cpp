
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_armed.h"

using aronnax::Entity;

using spacegun::COMPONENT_TYPE_ARMED;
using spacegun::Armed;

class ArmTest : public testing::Test {
  protected:
    virtual void SetUp() {
      entity_ = new Entity();
    }

    virtual void TearDown()
    {
      delete entity_;
    }

    Entity* entity_;
};

TEST_F(ArmTest, getType) {
  Armed c(entity_);

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_ARMED);
}

TEST_F(ArmTest, getWeaponEntity) {
  Armed c(entity_);

  auto actual = c.getWeapon();

  EXPECT_EQ(actual, entity_);
}

