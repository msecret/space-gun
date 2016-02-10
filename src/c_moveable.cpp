
#include "./c_moveable.h"

namespace spacegun {

  extern const std::string COMPONENT_TYPE_MOVEABLE;

  std::string Moveable::getType()
  {
    return COMPONENT_TYPE_MOVEABLE;
  } 

  aronnax::Vector2d Moveable::getVel()
  {
    return vel_;
  }

  void Moveable::setVel(aronnax::Vector2d newVel)
  {
    vel_ = newVel;
  }

}
