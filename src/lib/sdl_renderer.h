
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include "SDL2/SDL_video.h"

#include "renderer.h"

namespace aronnax {

class SDLRenderer : public Renderer
{
  public:
    SDLRenderer() {};
    void render(const uint32_t dt);

};

}

#endif
