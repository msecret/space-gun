
#include "./c_moveable.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_MOVEABLE;

  const string Moveable::getType()
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

  aronnax::Vector2d Moveable::getPos()
  {
    return pos_;
  }

  void Moveable::setPos(aronnax::Vector2d newPos)
  {
    pos_ = newPos;
  }

  void Moveable::move(aronnax::Vector2d vel)
  {
    pos_ += vel;
  }
}
