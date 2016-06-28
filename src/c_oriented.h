
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

  class Oriented : public aronnax::Component
  {
    public:
      Oriented(Moveable& moveable) :
        moveable_(&moveable)
      {};
      const string getType() {
        return COMPONENT_TYPE_ORIENTED;
      };
      // TODO move to Moveable
      float getNormalizedAngle();
      bool facingNorth();

    private:
      Moveable* moveable_;

  };

}

#endif
