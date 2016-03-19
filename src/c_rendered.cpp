
#include <string>

#include <SDL2/SDL.h>

#include "lib/units.h"

#include "./c_rendered.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_RENDERED;

  Rendered::Rendered() :
    texture_(nullptr)
  {
    //texture_ = createTexture(color_);
  }

  const string Rendered::getType()
  {
    return COMPONENT_TYPE_RENDERED;
  }

  SDL_Texture* Rendered::getTexture()
  {
    return texture_;
  }
}
