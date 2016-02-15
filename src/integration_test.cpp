
#include <functional>
#include <iostream>
#include <memory>
#include <stdio.h>

#include "SDL2/SDL.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "lib/clock.h"
#include "lib/component.h"
#include "lib/entity.h"
#include "lib/manager.h"
#include "lib/sdl_renderer.h"

#include "c_moveable.h"
#include "s_movement.h"


namespace spacegun {
TEST(Integrationtest, MainFunction) {
  using namespace std;
  using namespace std::placeholders;
  using namespace aronnax;

  Clock clock;
  Vector2d initVA = { 1, 2 };
  Vector2d initVB = { 1, 2 };
  Vector2d initP = { 0, 0 };
  Moveable moveableA(initVA);
  Moveable moveableB(initVB);
  Movement movementSys;
  Manager manager;

  Entity* aa = new Entity();
  Entity* ab = new Entity();

  aa->addComponent(&moveableA);
  ab->addComponent(&moveableB);

  manager.addEntity(*aa);
  manager.addEntity(*ab);
  manager.addSystem(&movementSys);

  function<void(const uint32_t)> f_update = bind(
      &Manager::update, &manager, _1);

  clock.onConstantly(f_update);

  auto actual = aa->getPos();
  EXPECT_EQ(initP, actual);

  clock.tick();
  auto advance1 = initP + initVA;
  actual = aa->getPos();
  EXPECT_EQ(advance1, actual);
}
}
