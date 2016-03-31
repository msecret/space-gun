
#include <gtest/gtest.h>

#include "../c_damageable.h"

using spacegun::COMPONENT_TYPE_DAMAGEABLE;
using spacegun::Damageable;

TEST(Damageable, Constructor) {
  Damageable c;

  auto actual = c.getHealth();
  EXPECT_EQ(actual, 0);

  auto expectedHealth = 120;

  Damageable c2(expectedHealth);
  actual = c2.getHealth();


  EXPECT_EQ(actual, expectedHealth);
}

TEST(Damageable, getType) {
  Damageable c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_DAMAGEABLE);
}

TEST(Damageable, applyDamage) {
  Damageable c(100);
  float damage = 25.5;
  float expected = 100 - damage;

  c.applyDamage(damage);
  auto actual = c.getHealth();

  EXPECT_EQ(actual, expected);
}
