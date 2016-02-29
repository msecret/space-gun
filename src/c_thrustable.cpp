
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

  double Thrustable::getFactor()
  {
    return factor_;
  }

  void Thrustable::setFactor(double factor)
  {
    factor_ = factor;
  }

}
