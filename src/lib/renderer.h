
#ifndef _h_Renderer
#define _h_Renderer

#include <memory>

#include "SDL2/SDL.h"

#include "units.h"

namespace aronnax {

  class IRenderer
  {
    public:
      virtual ~IRenderer() {};
      virtual void render() = 0;
      virtual void beforeRender() = 0;
      virtual void afterRender() = 0;
      virtual void drawCircle(const Vector2d& pos, const Vector2d& r) = 0;
      virtual void drawRectangle(const Vector2d& pos, const Vector2d& box,
          const Color& color) = 0;
      virtual void drawPolygon(const Vector2d& pos) = 0;
      virtual SDL_Texture* createTexture(SDL_Surface& s) = 0;
  };

}

#endif
