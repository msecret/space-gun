
#include "alias.h"
#include "c_rectangular.h"

namespace spacegun {
  using namespace std;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_RECTANGULAR;

  Rectangular::Rectangular(float w, float h)
  {
    box_.x = w;
    box_.y = h;
  }

  const string Rectangular::getType()
  {
    return COMPONENT_TYPE_RECTANGULAR;
  }

  float Rectangular::getW()
  {
    return box_.x;
  }

  float Rectangular::getH()
  {
    return box_.y;
  }

  void Rectangular::setW(float w)
  {
    box_.x = w;
  }

  void Rectangular::setH(float h)
  {
    box_.y = h;
  }

}
