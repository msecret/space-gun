
#ifndef _h_Evented
#define _h_Evented

#include <string>

#include "lib/component.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_EVENTED = "evented";

  class Evented : public aronnax::Component
  {
    public:
      Evented() {};
      const string getType() { return COMPONENT_TYPE_EVENTED; }
  };
}

#endif
