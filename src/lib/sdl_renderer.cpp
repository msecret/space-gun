
#include <iostream>
#include <memory>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "sdl_renderer.h"

namespace aronnax {

SDLRenderer::SDLRenderer(SDL_Window* window)
{
  screen_.reset(window, SDL_DestroyWindow);
  SDL_Renderer *rawPtr = nullptr;
  rawPtr = SDL_CreateRenderer(window, -1, 0);
  if (rawPtr == nullptr) {
    std::cerr << "creating renderer failed: " << SDL_GetError() << std::endl;
  }
  renderer_.reset(rawPtr, SDL_DestroyRenderer);
}

void SDLRenderer::render(const uint32_t dt)
{
}

void SDLRenderer::beforeRender()
{
  // TODO move bg color elsewhere
  SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer_.get());

  SDL_RenderPresent(renderer_.get());
}

void SDLRenderer::afterRender()
{

}

}
