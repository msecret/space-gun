
#include "c_rectangular.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_RECTANGULAR;

  Rectangular::Rectangular(double w, double h)
  {
    box_.x = w;
    box_.y = h; 
  }

  const string Rectangular::getType()
  {
    return COMPONENT_TYPE_RECTANGULAR;
  }

  double Rectangular::getW()
  {
    return box_.x;
  }

  double Rectangular::getH()
  {
    return box_.y;
  }

  void Rectangular::setW(double w)
  {
    box_.x = w;
  }

  void Rectangular::setH(double h)
  {
    box_.y = h;
  }

}
