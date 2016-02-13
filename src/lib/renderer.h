
#ifndef _h_Renderer
#define _h_Renderer

#include <memory>

#include "units.h"

namespace aronnax {

  class IRenderer
  {
    public:
      virtual ~IRenderer() {};
      virtual void render() = 0;
      virtual void beforeRender() = 0;
      virtual void afterRender() = 0;
      virtual void drawCircle(const Vector2d pos, const Vector2d r) = 0;
      virtual void drawRectangle(const Vector2d pos, const Vector2d box) = 0;
      virtual void drawPolygon(const Vector2d pos) = 0;
  };

}

#endif
