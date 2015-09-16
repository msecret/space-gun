
#include <iostream>
#include <memory>
#include <stdio.h>

#include "ball.h"
#include "lib/entity.h"
#include "lib/time.h"

void test_c(const uint32_t d)
{
  int s = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      s = i + j;
    } 
  }
}

void test_f(const uint32_t d)
{
  int s = 0;
  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 1000; j++) {
      s = i + j;
    } 
  }
}

int main()
{
  using namespace std::placeholders;

  std::cout << "poop\n";
  aronnax::Entity *ball = spacegun::createBall();
  ball->v.x = 1.5;

  aronnax::Clock* clock = new aronnax::Clock();
  //std::function<void(const uint32_t)> f_update= std::bind(&aronnax::Entity::update, ball, _1);
  std::function<void(const uint32_t)> f_update = test_c;
  std::function<void(const uint32_t)> f_frame = test_f;

  clock->onConstantly(f_update);
  clock->onEveryFrame(f_frame);

  clock->start();

  return 0;
}
