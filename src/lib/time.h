
#ifndef _h_Time
#define _h_Time

#include <chrono>
#include <cstdint>
#include <memory>

namespace aronnax {

class Clock
{
  private:
    bool isStarted_;

    void tick_();


  public:

    Clock(){};

    void start();
    void stop();

    bool started();

    void onConstantly();
    void onEveryFrame();
    void onEverySecs(const uint64_t secs);

    void singleStep();
};

}

#endif
