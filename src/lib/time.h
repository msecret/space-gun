
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

    std::function<void(const uint32_t)>& f_onConstantly_;
    std::function<void(const uint32_t)>& f_onEveryFrame_;

  public:

    Clock() {};

    void start();
    void stop();
    bool isStarted();

    void tick();
    void tickConstantly(uint32_t d);
    void tickEveryFrame(const uint32_t d);

    void onConstantly(std::function<void(const uint32_t)>& def);
    void onEveryFrame(std::function<void(const uint32_t)>& def);
    //void onEverySecs(double secs, std::function<void()>);

};

}

#endif
