
#ifndef _h_Smasher
#define _h_Smasher

#include <string>

#include "lib/component.h"
#include "lib/units.h"

#include "c_moveable.h"

namespace spacegun {
  using namespace std;
  using namespace aronnax;

  const string COMPONENT_TYPE_SMASHER = "smasher";

  class Smasher : public aronnax::Component
  {
    public:
      Smasher(float dmg) :
        dmg_(dmg)
      {};
      const string getType() {
        return COMPONENT_TYPE_SMASHER;
      };
      float getDamage();

    private:
      float dmg_;

  };

}

#endif
