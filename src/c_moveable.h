
#ifndef _h_Moveable
#define _h_Moveable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {

  const std::string COMPONENT_TYPE_MOVEABLE = "moveable";

  class Moveable : public aronnax::Component
  {
    public:
      Moveable() {};
      Moveable(const aronnax::Vector2d& initialVel)
        : vel_(initialVel) {};
      std::string getType();
      aronnax::Vector2d getVel();
      void setVel(aronnax::Vector2d newVel);

    private:
      aronnax::Vector2d vel_;

  };
}

#endif
