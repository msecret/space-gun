
#include <string>

#include "lib/units.h"

#include "./c_boundable.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_BOUNDABLE;

  const string Boundable::getType()
  {
    return COMPONENT_TYPE_BOUNDABLE;
  }

  const Vector2d& Boundable::getBounds()
  {
    return bounds_;
  }

}
