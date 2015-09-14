
#ifndef _h_Time
#define _h_Time

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace aronnax {

class Clock 
{
  private:
    uint32_t previous_;
    uint32_t lag_;

    bool isStarted_;

    void launch_();
    uint32_t getCurrentTime_();

  public:

    Clock();

    void start();
    void stop();
    bool isStarted();

    void tick();
    void tickConstantly();
    void tickEveryFrame();

    void onConstantly();
    void onEveryFrame();
    void onEverySecs(double secs);

};

}

#endif
