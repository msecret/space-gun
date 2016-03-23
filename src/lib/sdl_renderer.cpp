
#include <iostream>
#include <math.h>
#include <memory>

#include "SDL2/SDL.h"

#include "sdl_renderer.h"
#include "units.h"

#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

namespace aronnax {

  //float RADTODEG = 180 / M_PI;

  SDLRenderer::~SDLRenderer()
  {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(&screen_);
  }

  SDLRenderer::SDLRenderer(SDL_Window* window):
    screen_(*window)
  {
    SDL_Renderer* rendererPtr = nullptr;
    rendererPtr = SDL_CreateRenderer(window, -1, 0);
    if (rendererPtr == nullptr) {
      std::cerr << "creating renderer failed: " << SDL_GetError() << std::endl;
    }
    renderer_ = rendererPtr;
  }

  void SDLRenderer::render()
  {
  }

  void SDLRenderer::beforeRender()
  {
    // TODO move bg color elsewhere
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
  }

  void SDLRenderer::afterRender()
  {
    SDL_RenderPresent(renderer_);
  }

  void SDLRenderer::drawRectangle(const Vector2d& pos,
                                  const Vector2d& box,
                                  SDL_Texture* texture,
                                  float angle
                                  )
  {
    SDL_Rect r;
    r.x = int(pos.x - box.x / 2);
    r.y = int(pos.y - box.x / 2);
    r.w = int(box.x);
    r.h = int(box.y);

    SDL_RenderCopyEx(
      renderer_,
      texture,
      NULL,
      &r,
      radiansToDegrees(angle),
      NULL,
      SDL_FLIP_NONE
    );
  }

  void SDLRenderer::drawCircle(const Vector2d& pos, const Vector2d& r)
  {
  }

  void SDLRenderer::drawPolygon(const Vector2d& pos)
  {
  }

  SDL_Texture* SDLRenderer::createTexture(SDL_Surface& s)
  {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, &s);

    if (texture == NULL) {
      // fprintf(stderr, "CreateTexture failed: %s\n", SDL_GetError());
      exit(1);
    }

    return texture;
  }

}
