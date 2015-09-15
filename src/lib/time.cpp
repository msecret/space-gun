
#include <cstdint>
#include <memory>
#include <vector>

#include "SDL/SDL.h"

#include "time.h"

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
  uint32_t current = getCurrentTime_();
  uint32_t elapsed = current - previous_;
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
  previous_ = getCurrentTime_();
  lag_ = 0.0;

  while (isStarted_) {
    tick();
  }
}

uint32_t Clock::getCurrentTime_()
{
  return SDL_GetTicks();
}

}
