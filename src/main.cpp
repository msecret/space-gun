
#include <iostream>
#include <stdio.h>

#include "ball.h"
#include "lib/entity.h"

int main()
{
  std::cout << "poop\n";
  aronnax::Entity *ball = spacegun::createBall();
  ball->v.x = 1.5;

  return 0;
}
