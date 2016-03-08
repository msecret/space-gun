
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

}
