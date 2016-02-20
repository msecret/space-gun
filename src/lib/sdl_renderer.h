
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include <memory>

#include "SDL2/SDL.h"

#include "renderer.h"
#include "units.h"

namespace aronnax {

class SDLRenderer : public IRenderer
{
  public:
    ~SDLRenderer();
    SDLRenderer(SDL_Window* window);
    void render();
    void beforeRender();
    void afterRender();
    void drawCircle(const Vector2d& pos, const Vector2d& r);
    void drawRectangle(const Vector2d& pos, const Vector2d& box,
        const Color& color);
    void drawPolygon(const Vector2d& pos);

  private:
    // TODO should this be a pointer?
    SDL_Window& screen_;
    SDL_Renderer* renderer_;
};

}

#endif
