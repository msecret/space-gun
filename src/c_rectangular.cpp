
#include <Box2D/Box2D.h>

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
    shape_ = new PolygonShape();
    shape_->SetAsBox(w / 2, h / 2);
  }

  Rectangular::~Rectangular()
  {
    delete shape_;
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
    shape_->SetAsBox(box_.x / 2, box_.y / 2);
  }

  void Rectangular::setH(float h)
  {
    box_.y = h;
    shape_->SetAsBox(box_.x / 2, box_.y / 2);
  }

  PolygonShape* Rectangular::getShape()
  {
    return shape_;
  }

}
