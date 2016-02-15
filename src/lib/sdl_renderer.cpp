
#include <iostream>
#include <memory>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "sdl_renderer.h"

namespace aronnax {

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

  void SDLRenderer::drawRectangle(const Vector2d& pos, const Vector2d& box) 
  {
    SDL_Rect r;
    r.x = int(pos.x);
    r.y = int(pos.y);
    r.w = int(box.x);
    r.h = int(box.y);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer_, &r);
  }

  void SDLRenderer::drawCircle(const Vector2d& pos, const Vector2d& r)
  {
  }

  void SDLRenderer::drawPolygon(const Vector2d& pos)
  {
  }

}
