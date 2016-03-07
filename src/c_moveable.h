
#ifndef _h_Moveable
#define _h_Moveable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_MOVEABLE = "moveable";

  class Moveable : public aronnax::Component
  {
    public:
      Moveable() {};
      Moveable(const aronnax::Vector2d& initialVel) :
        vel_(initialVel),
        pos_()
      {};
      Moveable(const aronnax::Vector2d& initialVel,
               const aronnax::Vector2d& initialPos) :
        vel_(initialVel),
        pos_(initialPos)
      {};
      const string getType();
      aronnax::Vector2d getVel();
      void setVel(aronnax::Vector2d newVel);
      aronnax::Vector2d getPos();
      void setPos(aronnax::Vector2d newPos);
      void move(aronnax::Vector2d vel);

    private:
      aronnax::Vector2d vel_;
      aronnax::Vector2d pos_;

  };
}

#endif
