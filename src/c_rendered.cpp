
#include <string>

#include <SDL2/SDL.h>

#include "lib/units.h"

#include "./c_rendered.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_RENDERED;

  Rendered::Rendered() :
    texture_(nullptr),
    surface_(nullptr)
  {
    //texture_ = createTexture(color_);
  }

  Rendered::~Rendered()
  {
    if (surface_) {
      SDL_FreeSurface(surface_);
    }
    if (texture_) {
      SDL_DestroyTexture(texture_);
    }
  }

  const string Rendered::getType()
  {
    return COMPONENT_TYPE_RENDERED;
  }

  void Rendered::init(SDL_Surface* s, SDL_Texture* t)
  {
    surface_ = s;
    texture_ = t;
  }

  SDL_Texture* Rendered::getTexture()
  {
    return texture_;
  }

  SDL_Surface* Rendered::getSurface()
  {
    return surface_;
  }
}
