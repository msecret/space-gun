
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include "SDL/SDL.h"

#include "renderer.h"

namespace aronnax {

class SDLRenderer
{
  public:
    SDLRenderer();
    void render(const uint32_t dt);

  private:
    SDL_Surface* screen_;

};

}

#endif
