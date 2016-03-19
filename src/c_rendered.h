
#ifndef _h_Rendered
#define _h_Rendered

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Component;

  const string COMPONENT_TYPE_RENDERED = "rendered";

  class Rendered: public Component
  {
    public:
      Rendered();
      const string getType();
      SDL_Texture* getTexture();

    private:
      SDL_Texture* texture_;

  };
}

#endif
