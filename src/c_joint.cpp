
#include <Box2D/Box2D.h>

#include "c_joint.h"

namespace spacegun {
  using std::string;

  extern const string COMPONENT_TYPE_JOINT;

  const string Joint::getType()
  {
    return COMPONENT_TYPE_JOINT;
  }
}
