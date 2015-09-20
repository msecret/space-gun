
#ifndef _h_Time
#define _h_Time

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

// TODO consider an alias for uint32_t to make easy to change
// TODO change name of onConstantly function list

namespace aronnax {

class Clock
{
  private:
    uint32_t previous_;
    uint32_t lag_;

    bool isStarted_;

    void launch_();
    uint32_t getCurrentTime_();

    std::vector<std::function<void(const uint32_t)>> f_constantlys_;
    std::vector<std::function<void(const uint32_t)>> f_everyFrames_;

  public:

    Clock() : previous_(0),
              lag_(0),
              isStarted_(false),
              f_constantlys_(),
              f_everyFrames_()
    {};

    void start();
    void stop();
    bool isStarted();

    void onConstantly(std::function<void(const uint32_t)>& def);
    void onEveryFrame(std::function<void(const uint32_t)>& def);
    //void onEverySecs(double secs, std::function<void()>);
    //
    void tick();
    void tickConstantly(uint32_t d);
    void tickEveryFrame(const uint32_t d);
};

}

#endif
