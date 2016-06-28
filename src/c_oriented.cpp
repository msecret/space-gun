
#include <cstdio>
#include <iostream>

#include "c_oriented.h"

#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

namespace spacegun {
  float Oriented::getNormalizedAngle()
  {
		float angle = radiansToDegrees(moveable_->getAngle());
    while (angle <= 0){
       angle += 360;
    }
    while (angle > 360){
       angle -= 360;
    }

    return angle;
  }

  bool Oriented::facingNorth()
  {
    auto angle = getNormalizedAngle();
    if (angle < 90 || angle > 270) {
      return true;
    }
    return false;
  }
}
