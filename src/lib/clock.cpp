
#include <iostream>
#include <stdio.h>

#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>
#include <vector>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "clock.h"

namespace aronnax {

void Clock::start()
{
  isStarted_ = true;
  launch_();
}

void Clock::stop()
{
  isStarted_ = false;
}

bool Clock::isStarted()
{
  return isStarted_;
}

void Clock::onConstantly(std::function<void(const uint32_t)>& def)
{
  f_constantlys_.push_back(def);
}

void Clock::onEveryFrame(std::function<void(const uint32_t)>& def)
{
  f_everyFrames_.push_back(def);
}


void Clock::tick()
{
  const uint32_t MS_PER_UPDATE = 8;
  const uint32_t MAX_LAG = 1000;
  uint32_t current = getCurrentTime_();
  uint32_t elapsed = current - previous_;
  if (elapsed > MAX_LAG) elapsed = MAX_LAG;
  previous_ = current;
  lag_ += elapsed;

  while (lag_ >= MS_PER_UPDATE) {
    tickConstantly(lag_);
    lag_ -= MS_PER_UPDATE;
  }

  tickEveryFrame(lag_);
}

void Clock::tickConstantly(const uint32_t d)
{
  for (unsigned int i = 0; i < f_constantlys_.size(); ++i) {
    f_constantlys_[i](d);
  }
}

void Clock::tickEveryFrame(const uint32_t d)
{
  for (unsigned int i = 0; i < f_everyFrames_.size(); ++i) {
    f_everyFrames_[i](d);
  }
}

void Clock::launch_()
{
  lag_ = 0.0;
  previous_ = getCurrentTime_();

  while (isStarted_) {
    tick();
  }
}

uint32_t Clock::getCurrentTime_()
{
  return SDL_GetTicks();
}

}
