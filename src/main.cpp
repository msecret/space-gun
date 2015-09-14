
#include <iostream>
#include <stdio.h>

#include "ball.h"
#include "lib/entity.h"

int main()
{
  std::cout << "poop\n";
  aronnax::Entity *ball = spacegun::createBall();
  ball->v.x = 1.5;

  Clock clock = new Clock();
  std::function<void(int)> f_update= std::bind(&Entity::update, &ball, _1);
  clock.onConstantly(f_update);

  return 0;
}
