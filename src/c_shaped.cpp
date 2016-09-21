
#include "c_shaped.h"
#include "c_rectangular.h"

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

  BaseShaped* Shaped::getShapeComponent()
  {
    return shapeComponent_;
  }

  Shape* Shaped::getShape()
  {
    return shapeComponent_->getShape();
  }

  Vector2d Shaped::getBoundingBox()
  {
    return shapeComponent_->getBoundingBox();
  }

}
