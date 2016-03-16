
#include "c_shaped.h"

namespace spacegun {

  extern const string COMPONENT_TYPE_SHAPED;

  const string Shaped::getType()
  {
    return COMPONENT_TYPE_SHAPED;
  }

  const string Shaped::getShapeType()
  {
    return shapeComponent_->getType();
  }

  /*
  Component* Shaped::getShape()
  {
    return shapeComponent_->getShape();
  }
  */
}
