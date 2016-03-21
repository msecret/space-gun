
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
      ~Rendered();
      const string getType();
      void init(SDL_Surface* s, SDL_Texture* t);
      SDL_Texture* getTexture();
      SDL_Surface* getSurface();

    private:
      SDL_Texture* texture_;
      SDL_Surface* surface_;

  };
}

#endif
