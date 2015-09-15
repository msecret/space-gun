
#include <cstdint>

#include "time.h"

namespace aronnax {

void Clock::launch_()
{
  previous_ = getCurrentTime_();
  lag_ = 0.0;

  while (isStarted_) {
    tick();
  }
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

void Clock::onConstantly(std::function<void(const uint32_t)>& def)
{
  f_onConstantly_ = def;
}

void Clock::onEveryFrame(std::function<void(const uint32_t)>& def)
{
  f_onEveryFrame_ = def;
}

void Clock::tickConstantly(const uint32_t d)
{
  if (f_onConstantly_) {
    f_onConstantly_(d);
  }
}

void Clock::tickEveryFrame(const uint32_t d)
{
  if (f_onEveryFrame_) {
    f_onEveryFrame_(d);
  }
}

void Clock::start()
{
  isStarted_ = true;
  start();
}

void Clock::stop()
{
  isStarted_ = false;
}

bool Clock::isStarted()
{
  return isStarted_;
}

}
