
#include <string>

#include "lib/units.h"

#include "c_thrustable.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_THRUSTABLE;

  const string Thrustable::getType()
  {
    return COMPONENT_TYPE_THRUSTABLE;
  }

  float Thrustable::getFactor()
  {
    return factor_;
  }

  void Thrustable::setFactor(float factor)
  {
    factor_ = factor;
  }

  void Thrustable::setUpFactor(float up)
  {
    directionFactors_[0] = up;
  }

  void Thrustable::setDownFactor(float down)
  {
    directionFactors_[2] = down;
  }

  float Thrustable::getUpFactor()
  {
    return directionFactors_[0];
  }

  float Thrustable::getDownFactor()
  {
    return directionFactors_[2];
  }

  void Thrustable::setRightFactor(float right)
  {
    directionFactors_[1] = right;
  }

  void Thrustable::setLeftFactor(float left)
  {
    directionFactors_[3] = left;
  }

  float Thrustable::getRightFactor()
  {
    return directionFactors_[1];
  }

  float Thrustable::getLeftFactor()
  {
    return directionFactors_[3];
  }

  bool Thrustable::isOrientedStrafe()
  {
    return isOrientedStrafe_;
  }
}
