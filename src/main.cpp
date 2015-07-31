
#include <iostream>

#include "ball.h"
#include "lib/entity.h"

int main()
{
  std::cout << "Hello World\n";
  Entity *ball = game::createBall();

  return 0;
}
