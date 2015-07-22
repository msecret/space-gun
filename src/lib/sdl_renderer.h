
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include "SDL.h"

class SDLRenderer
{
  public:
    SDLRenderer();
    void render();

  private:
    SDL_Surface* screen_;

}

#endif
