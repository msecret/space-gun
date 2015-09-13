
#ifndef _h_Time
#define _h_Time

#include <chrono>
#include <cstdint>
#include <memory>

namespace aronnax {

class Clock 
{
  private:
    uint64_t timeCycles_;
    float timeScale_;
    bool isPaused_;

    static float cyclesPerSecond_;

    static inline uint64_t secondsToCycles(float timeSeconds);

    static inline float cylesToSeconds(uint64_t timeCycles);

  public:

    Clock(float startTimeSeconds=0.0f) :
      timeCycles_(secondsToCycles(startTimeSeconds)),
      timeScale_(1.0f),
      isPaused_(false){ };

    void start();
    void stop();

    void pause();
    void unpause();
    bool isPaused() const;

    void onEverySecs(const uint64_t secs);

    void singleStep();

};

}

#endif
