
#include <cstdint>

#include "time.h"

namespace aronnax {

  Clock::launch_()
  {
    const double MS_PER_UPDATE = 8;
    previous_ = getCurrentTime_();
    double lag = 0.0;

    while (isStarted_) {
      tick();
    }

  }

  Clock::tick()
  {
    double current = getCurrentTime_();
    double elapsed = current - previous_;
    previous_ = current;
    lag += elapsed;

    processInput();

    while (lag >= MS_PER_UPDATE)
    {
      onConstantly();
      lag -= MS_PER_UPDATE;
    }

    onEveryFrame();
  }

}
