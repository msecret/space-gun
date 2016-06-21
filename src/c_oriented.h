
#ifndef _h_Oriented
#define _h_Oriented

#include <string>

#include "lib/component.h"
#include "lib/units.h"

#include "c_moveable.h"

namespace spacegun {
  using namespace std;
  using namespace aronnax;

  const string COMPONENT_TYPE_ORIENTED = "oriented";
  const Vector2d ORIENTATATION_N = Vector2d(0, -1);
  const Vector2d ORIENTATATION_E = Vector2d(1, 0);
  const Vector2d ORIENTATATION_S = Vector2d(0, 1);
  const Vector2d ORIENTATATION_W = Vector2d(-1, 0);

  class Oriented : public aronnax::Component
  {
    public:
      Oriented(Moveable& moveable) :
        moveable_(&moveable)
      {};
      const string getType() {
        return COMPONENT_TYPE_ORIENTED;
      };

    private:
      Moveable* moveable_;

  };

}

#endif
