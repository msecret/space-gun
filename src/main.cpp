
#include <iostream>
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
  std::function<void(const int)> f_update= std::bind(&aronnax::Entity::update, ball, _1);
  clock->onConstantly(f_update);

  return 0;
}
