
#include <iostream>
#include <math.h>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sdl_renderer.h"
#include "units.h"

#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

namespace aronnax {
  using std::cout;
  using std::cerr;
  using std::endl;

  //float RADTODEG = 180 / M_PI;

  SDLRenderer::~SDLRenderer()
  {
    TTF_CloseFont(font_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(screen_);
  }

  SDLRenderer::SDLRenderer(SDL_Window* window):
    screen_(window)
  {
    SDL_Renderer* rendererPtr = nullptr;
    rendererPtr = SDL_CreateRenderer(window, -1, 0);
    if (rendererPtr == nullptr) {
      std::cerr << "creating renderer failed: " << SDL_GetError() << std::endl;
    }
    renderer_ = rendererPtr;

    TTF_Font* fixed = TTF_OpenFont("fonts/DejaVuSansMono.ttf", 16);
    if (fixed == NULL) {
      cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
      TTF_Quit();
      SDL_Quit();
      throw std::runtime_error(TTF_GetError());
    }
    font_ = fixed;

    auto filePath = "./img/space.jpg";
    auto s = IMG_Load(filePath);
    if (s == NULL) {
      throw std::runtime_error(SDL_GetError());
    }
    bg_ = SDL_CreateTextureFromSurface(renderer_, s);
    if (bg_ == NULL) {
      throw std::runtime_error(SDL_GetError());
    }
  }

  void SDLRenderer::render()
  {
  }

  void SDLRenderer::beforeRender()
  {
    // TODO move bg color elsewhere
    SDL_RenderClear(renderer_);
    SDL_SetTextureBlendMode(bg_, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(renderer_, bg_, NULL, NULL);
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
    auto halfW = box.x / 2;
    auto halfH = box.y / 2;
    r.x = pos.x - halfW;
    r.y = pos.y - halfH;
    r.w = int(box.x);
    r.h = int(box.y);

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer_, texture);

    SDL_RenderCopyEx(
      renderer_,
      texture,
      NULL,
      &r,
      radiansToDegrees(angle) + 90.0f,
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
    SDL_Color sdlCol = { color.r, color.g, color.b, color.a };
    SDL_Surface* surface = TTF_RenderText_Solid(font_,
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

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer_, texture, NULL, &messageRect);
    SDL_DestroyTexture(texture);
  }

  SDL_Texture* SDLRenderer::createTexture(SDL_Surface& s)
  {
    auto windowFormat = SDL_GetWindowPixelFormat(screen_);
    SDL_PixelFormat *format;
    format->format = windowFormat;
    auto converedS = SDL_ConvertSurface(&s, format, NULL);
    if (converedS == NULL) throw std::runtime_error(SDL_GetError());

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, converedS);

    if (texture == NULL) {
      // fprintf(stderr, "CreateTexture failed: %s\n", SDL_GetError());
      throw std::runtime_error(SDL_GetError());
      exit(1);
    }

    return texture;
  }

  SDL_Surface* SDLRenderer::loadImg(const string& filePath)
  {
    auto cimgPath = filePath.c_str();
    auto s = IMG_Load(cimgPath);
    return s;
  }
}
