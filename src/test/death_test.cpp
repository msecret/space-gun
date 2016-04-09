
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_damageable.h"
#include "../c_mortal.h"
#include "../c_moveable.h"
#include "../s_death.h"

using aronnax::EV_PLAYER_DEATH;
using aronnax::Entity;
using aronnax::EvPlayerDeath;
using aronnax::Vector2d;

using spacegun::COMPONENT_TYPE_MORTAL;
using spacegun::Death;
using spacegun::Damageable;
using spacegun::Mortal;
using spacegun::Moveable;

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

TEST(Death, onAddEntity) {
  float initH = 50;
  Vector2d initV = { 1, 0 };
  Vector2d initP = { 50, 50 };
  Moveable moveable(initV, initP);
  Damageable damageable(initH);
  damageable.setDamageFactor(1.0f);
  Mortal mortal;

  auto e = new Entity();
  e->addComponent(&damageable);
  e->addComponent(&moveable);
  e->addComponent(&mortal);

  Death s;
  s.onAddEntity(*e);

  moveable.setPos(Vector2d(250, 250));
  damageable.applyDamage(15.0f);

  EvPlayerDeath ev;
  e->emit(EV_PLAYER_DEATH, &ev);

  auto actualP = moveable.getPos();
  auto actualV = moveable.getVel();
  auto actualH = damageable.getHealth();

  EXPECT_FLOAT_EQ(actualP.x, 60);
  EXPECT_FLOAT_EQ(actualV.x, 0);
  EXPECT_FLOAT_EQ(actualH, initH);

  delete e;
}
