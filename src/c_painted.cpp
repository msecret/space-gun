
#include <string>

#include <SDL2/SDL.h>

#include "lib/units.h"

#include "./c_painted.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_PAINTED;

  Painted::Painted() :
    color_(),
    texture_(nullptr)
  {
    texture_ = createTexture(color_);
  }

  Painted::Painted(const aronnax::Color& c) :
    color_(c),
    texture_(nullptr)
  {
    texture_ = createTexture(c);
  }

  Painted::Painted(const uint8_t r,
              const uint8_t g,
              const uint8_t b,
              const uint8_t a)
  {
    aronnax::Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;

    color_ = c;
  }

  const string Painted::getType()
  {
    return COMPONENT_TYPE_PAINTED;
  }

  const aronnax::Color& Painted::getColor()
  {
    return this->color_;
  }

  void Painted::setColor(const aronnax::Color& color)
  {
    color_ = color;
  }

  SDL_Texture* Painted::getTexture()
  {
    return texture_;
  }

  SDL_Texture* createTexture(const Color& color)
  {
    SDL_Surface* s;

    return SDL_CreateTextureFromSurface(s);
  }
}
