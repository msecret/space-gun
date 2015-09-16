
#include <iostream>
#include <memory>
#include <stdio.h>

#include "ball.h"
#include "lib/entity.h"
#include "lib/time.h"

int main()
{
  using namespace std::placeholders;

  std::cout << "poop\n";
  aronnax::Entity *ball = spacegun::createBall();
  ball->v.x = 1.5;

  aronnax::Clock* clock = new aronnax::Clock();
  std::function<void(const uint32_t)> f_update= std::bind(&aronnax::Entity::update, ball, _1);

  clock->onConstantly(f_update);

  clock->start();

  return 0;
}
