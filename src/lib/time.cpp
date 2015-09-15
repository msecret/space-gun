
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
    tickConstantly();
    lag_ -= MS_PER_UPDATE;
  }

  tickEveryFrame();
}

void onConstantly(std::function<void(const int)>& def)
{

}

void Clock::tickConstantly()
{
  f_onConstantly_();
}

void Clock::tickEveryFrame()
{
  f_onEveryFrame_();
}

}
