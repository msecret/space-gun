
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
  c.setDamageFactor(1.0f);
  float damage = 25.5;
  float expected = 100 - damage;

  c.applyDamage(damage);
  auto actual = c.getHealth();

  EXPECT_EQ(actual, expected);
}

TEST(Damageable, resetHealth) {
  float expected = 100;
  Damageable c(expected);
  c.setDamageFactor(1.0f);
  c.applyDamage(40);
  c.applyDamage(20);

  c.resetHealth();

  auto actual = c.getHealth();

  EXPECT_FLOAT_EQ(actual, expected);
}
