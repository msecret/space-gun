
#include "lib/entity.h"
#include "lib/sdl_renderer.h"

#include "c_sprited.h"
#include "c_moveable.h"
#include "c_oriented.h"
#include "c_rendered.h"
#include "c_painted.h"
#include "c_shaped.h"
#include "s_sdl_paint_renderer.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;

  extern const string COMPONENT_TYPE_PAINTED;

  SDLPaintRenderer::SDLPaintRenderer()
  {
    renderer_ = nullptr;
  }

  SDLPaintRenderer::SDLPaintRenderer(SDLRenderer* renderer) :
    renderer_(renderer)
  { }

  void SDLPaintRenderer::init(Entities& entities)
  {
    for (auto e : entities) {
      initRectangle(*e);
    }
  }

  void SDLPaintRenderer::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->renderRectangle(dt, *e);
    }
  }

  const string& SDLPaintRenderer::getType()
  {
    return COMPONENT_TYPE_PAINTED;
  }

  void SDLPaintRenderer::renderRectangle(const uint32_t dt,
      Entity& entity)
  {
    if (renderer_ == nullptr) {
      // TODO this is techincally an error condition, what should be done?
      return;
    }

    auto shaped = entity.getComponent<Shaped>(COMPONENT_TYPE_SHAPED);
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto rendered = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);

    auto box = shaped->getBoundingBox();
    Vector2d pos = moveable->getPos();
    auto texture = rendered->getTexture();
    auto angle = moveable->getAngle();

    renderer_->drawRectangle(pos, box, texture, angle);
  }

  void SDLPaintRenderer::initRectangle(Entity& entity)
  {
    SDL_Surface *s;
    SDL_Texture *t;
    auto r = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);
    auto shaped = entity.getComponent<Shaped>(COMPONENT_TYPE_SHAPED);

    auto boundBox = shaped->getBoundingBox();
    auto width = boundBox.x;
    auto height = boundBox.y;

    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    auto p = entity.getComponent<Painted>(COMPONENT_TYPE_PAINTED);
    auto color = p->getColor();

    if (entity.hasComponent(COMPONENT_TYPE_ORIENTED)) {
      SDL_Rect majorPart = { width * 0.2, 0, width * 0.8, height };
      SDL_Rect minorPart = { 0, 0, width * 0.2, height };
      SDL_FillRect(s, &majorPart, SDL_MapRGBA(s->format,
            color.r,
            color.g,
            color.b,
            color.a));
      SDL_FillRect(s, &minorPart, SDL_MapRGBA(s->format,
            250,
            250,
            250,
            255));
    } else {
      SDL_FillRect(s, NULL, SDL_MapRGBA(s->format,
            color.r,
            color.g,
            color.b,
            color.a));
    }

    t = renderer_->createTexture(*s);

    if (color.a < 255) {
      SDL_SetTextureAlphaMod(t, color.a);
      SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    }

    r->init(s, t);
  }
}

