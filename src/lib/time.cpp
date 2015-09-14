
#include <cstdint>

#include "time.h"

namespace aronnax {

void Clock::launch_()
{
  const uint32_t MS_PER_UPDATE = 8;
  previous_ = getCurrentTime_();
  uint32_t lag_ = 0.0;

  while (isStarted_) {
    tick();
  }
}

void Clock::tick()
{
  uint32_t current = getCurrentTime_();
  uint32_t elapsed = current - previous_;
  previous_ = current;
  lag_ += elapsed;

  while (lag_ >= MS_PER_UPDATE) {
    tickConstantly();
    lag_ -= MS_PER_UPDATE;
  }

  tickEveryFrame();
}

void Clock::tickConstantly()
{
  f_onConstantly_();
}

void Clock::tickEveryFrame()
{
  f_onEveryFrame_();
}
