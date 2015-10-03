
#ifndef _h_Renderer
#define _h_Renderer

#include "units.h"

namespace aronnax {

class Renderer
{
  public:
    virtual void render() = 0;
    virtual void beforeRender() = 0;
    virtual void afterRender() = 0;
    virtual void drawCircle(const Vector2d pos, const Vector2d box) = 0;
};

}

#endif
