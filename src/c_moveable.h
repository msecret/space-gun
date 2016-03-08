
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
      Moveable();
      Moveable(const Vector2d& initialVel,
               const Vector2d& initialPos);
      const string getType();
      Vector2d getVel();
      void setVel(Vector2d newVel);
      Vector2d getPos();
      void setPos(Vector2d newPos);
      void move(Vector2d vel);

    private:
      Body* body_;
      BodyDef bodyDef_;

  };
}

#endif
