
#include "c_shaped.h"
#include "c_rectangular.h"

namespace spacegun {

  extern const string COMPONENT_TYPE_SHAPED;

  template <class TShape>
  const string Shaped<TShape>::getType()
  {
    return COMPONENT_TYPE_SHAPED;
  }

  template <class TShape>
  const string Shaped<TShape>::getShapeType()
  {
    return shapeComponent_->getType();
  }

  template <class TShape>
  TShape* Shaped<TShape>::getShapeComponent()
  {
    auto casted = static_cast<TShape*>(shapeComponent_);
    return casted;
  }

  template <class TShape>
  Shape* Shaped<TShape>::getShape()
  {
    auto casted = static_cast<TShape*>(shapeComponent_);
    return casted->getShape();
  }

  template class Shaped<Rectangular>;
}
