
#ifndef _h_Moveable
#define _h_Moveable

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_MOVEABLE = "moveable";

  class Moveable : public aronnax::Component
  {
    public:
      Moveable() :
        body_(nullptr)
      { }
      Moveable(const aronnax::Vector2d& initialVel) :
        body_(nullptr),
        vel_(initialVel),
        pos_()
      { };
      Moveable(const aronnax::Vector2d& initialVel,
               const aronnax::Vector2d& initialPos) :
        body_(nullptr),
        vel_(initialVel),
        pos_(initialPos)
      { };
      const string getType();
      aronnax::Vector2d getVel();
      void setVel(aronnax::Vector2d newVel);
      aronnax::Vector2d getPos();
      void setPos(aronnax::Vector2d newPos);
      void move(aronnax::Vector2d vel);

    private:
      aronnax::Vector2d vel_;
      aronnax::Vector2d pos_;
      Body* body_;
      BodyDef bodyDef_;

  };
}

#endif
