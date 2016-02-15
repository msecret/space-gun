
#ifndef _h_Evented
#define _h_Evented

#include <string>

#include "lib/component.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_EVENTED = "evented";
  const unsigned int EV_SDL_EVENT = 1;

  class Evented : public aronnax::Component
  {
    public:
      Evented() {};
      const string getType();
  };
}

#endif
