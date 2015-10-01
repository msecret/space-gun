
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include <memory>

#include "SDL2/SDL.h"

#include "renderer.h"
#include "units.h"

namespace aronnax {

class SDLRenderer : public Renderer
{
  public:
    SDLRenderer() {};
    ~SDLRenderer();
    SDLRenderer(SDL_Window* window);
    void render();
    void beforeRender();
    void afterRender();
    void drawCircle(const Vector2d pos, const Vector2d box);

  private:
    std::shared_ptr<SDL_Window> screen_;
    std::shared_ptr<SDL_Renderer> renderer_;

};

}

#endif
