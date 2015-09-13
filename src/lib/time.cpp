
#include <cstdint>

#include "time.h"

namespace aronnax {

  inline uint64_t Clock::secondsToCycles(float timeSeconds)
  {
    return (uint64_t)(timeSeconds * cyclesPerSecond_);
  }

  inline float Clock::cylesToSeconds(uint64_t timeCycles)
  {
    return (float)timeCycles / cyclesPerSecond_;
  }

  Clock::void init()
  {
    cyclesPerSecond_ = (F32)
  }

  uint64_t Clock::getTimeCycles() const
  {
    return timeCycles_;
  }

  float Clock::calcDeltaSeconds(const Clock& other)
  {

  }

}
