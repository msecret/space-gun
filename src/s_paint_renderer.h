
#ifndef _h_PaintRenderer
#define _h_PaintRenderer

#include <cstdint>

#include "lib/entity.h"
#include "lib/sdl_renderer.h"
#include "lib/system.h"

#include "constants.h"
#include "c_sprited.h"
#include "c_moveable.h"
#include "c_oriented.h"
#include "c_rendered.h"
#include "c_painted.h"
#include "c_shaped.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::SDLRenderer;
  using aronnax::System;

  template <typename TRenderer>
  class PaintRenderer: public System
  {
    public:
      PaintRenderer();
      PaintRenderer(TRenderer* renderer);
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities);
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      TRenderer* renderer_;
      void renderRectangle(const uint32_t dt, Entity&);
      void initRectangle(Entity&);
      Vector2d transformForDrawing(const Vector2d& value);


  };

  extern const string COMPONENT_TYPE_PAINTED;

  template <class TRenderer>
  PaintRenderer<TRenderer>::PaintRenderer()
  {
    renderer_ = nullptr;
  }

  template <class TRenderer>
  PaintRenderer<TRenderer>::PaintRenderer(TRenderer* renderer) :
    renderer_(renderer)
  { }

  template <class TRenderer>
  void PaintRenderer<TRenderer>::init(Entities& entities)
  {
    for (auto e : entities) {
      initRectangle(*e);
    }
  }

  template <class TRenderer>
  void PaintRenderer<TRenderer>::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->renderRectangle(dt, *e);
    }
  }

  template <class TRenderer>
  const string& PaintRenderer<TRenderer>::getType()
  {
    return COMPONENT_TYPE_PAINTED;
  }

  template <class TRenderer>
  void PaintRenderer<TRenderer>::renderRectangle(const uint32_t dt,
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
    auto transformedBox = transformForDrawing(box);
    auto transformedPos = transformForDrawing(pos);
    auto texture = rendered->getTexture();
    auto angle = moveable->getAngle();
    // TODO add transform for drawing

    renderer_->drawRectangle(transformedPos, transformedBox, texture, angle);
  }

  template <class TRenderer>
  void PaintRenderer<TRenderer>::initRectangle(Entity& entity)
  {
    SDL_Surface *s;
    SDL_Texture *t;
    auto r = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);
    auto shaped = entity.getComponent<Shaped>(COMPONENT_TYPE_SHAPED);

    auto boundBox = shaped->getBoundingBox();
    auto width = boundBox.x;
    auto height = boundBox.y;

    // TODO move to renderer
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
      // TODO move to renderer
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

  template <class TRenderer>
  Vector2d PaintRenderer<TRenderer>::transformForDrawing(const Vector2d& val)
  {
    Vector2d transformed;
    transformed.x = val.x * DRAW_FACTOR;
    transformed.y = val.y * DRAW_FACTOR;
    return transformed;
  }
}

#endif

