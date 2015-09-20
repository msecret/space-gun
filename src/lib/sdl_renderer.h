
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include <memory>

#include "SDL2/SDL.h"

#include "renderer.h"

namespace aronnax {

class SDLRenderer : public Renderer
{
  public:
    SDLRenderer() {};
    SDLRenderer(SDL_Window* window);
    void render();
    void beforeRender();
    void afterRender();

  private:
    std::shared_ptr<SDL_Window> screen_;
    std::shared_ptr<SDL_Renderer> renderer_;

};

}

#endif
