
#include <iostream>
#include <math.h>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sdl_renderer.h"
#include "units.h"

#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

namespace aronnax {
  using std::cout;
  using std::cerr;

  //float RADTODEG = 180 / M_PI;

  SDLRenderer::~SDLRenderer()
  {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(&screen_);
    TTF_Quit();
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

    if (TTF_Init() != 0) {
      cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
      SDL_Quit();
      exit(1);
    }
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

  void SDLRenderer::drawText(
        const Vector2d& pos,
        string message,
        const Color& color)
  {
    if(!TTF_WasInit()) {
      cerr << "TTF_Init failed " << TTF_GetError() << endl;
      exit(1);
    }
    TTF_Font* fixed = TTF_OpenFont("./DejaVuSansMono.ttf", 16);
    if (fixed == NULL) {
      cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
      TTF_Quit();
      SDL_Quit();
      exit(1);
    }
    SDL_Color sdlCol = { color.r, color.g, color.b };
    SDL_Surface* surface = TTF_RenderText_Solid(fixed,
        message.c_str(), sdlCol);
    if (surface == NULL) {
      cerr << "TTF surface Failed: " << TTF_GetError() << endl;
      TTF_Quit();
      SDL_Quit();
      exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);

    int width = surface->w;
    int height = surface->h;

    SDL_Rect messageRect;
    messageRect.x = pos.x;
    messageRect.y = pos.y;
    messageRect.w = width;
    messageRect.h = height;

    SDL_RenderCopy(renderer_, texture, NULL, &messageRect);
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
