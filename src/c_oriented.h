
#ifndef _h_Oriented
#define _h_Oriented

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;
  using namespace aronnax;

  const string COMPONENT_TYPE_ORIENTED = "oriented";

  class Oriented : public aronnax::Component
  {
    public:
      Oriented() {};
      const string getType() {
        return COMPONENT_TYPE_ORIENTED;
      };
  };

}

#endif
