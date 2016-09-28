
#ifndef _h_SpriteRenderer_
#define _h_SpriteRenderer

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

#include "c_moveable.h"
#include "c_rendered.h"
#include "c_shaped.h"
#include "c_sprited.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::System;

  template <typename TRenderer>
  class SpriteRenderer: public System
  {
    public:
      SpriteRenderer();
      SpriteRenderer(TRenderer* renderer);
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities);
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      TRenderer* renderer_;
      void renderSprite(const uint32_t dt, Entity&);
      void initSprite(Entity&);

  };

  extern const string COMPONENT_TYPE_SPRITED;

  template <class TRenderer>
  SpriteRenderer<TRenderer>::SpriteRenderer()
  {
    renderer_ = nullptr;
  }

  template <class TRenderer>
  SpriteRenderer<TRenderer>::SpriteRenderer(TRenderer* renderer) :
    renderer_(renderer)
  { }

  template <class TRenderer>
  void SpriteRenderer<TRenderer>::init(Entities& entities)
  {
    for (auto e : entities) {
      initSprite(*e);
    }
  }

  template <class TRenderer>
  void SpriteRenderer<TRenderer>::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->renderSprite(dt, *e);
    }
  }

  template <class TRenderer>
  const string& SpriteRenderer<TRenderer>::getType()
  {
    return COMPONENT_TYPE_SPRITED;
  }

  template <class TRenderer>
  void SpriteRenderer<TRenderer>::renderSprite(const uint32_t dt,
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

  template <class TRenderer>
  void SpriteRenderer<TRenderer>::initSprite(Entity& entity)
  {
    SDL_Surface *s;
    SDL_Texture *t;
    auto r = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);
    auto shaped = entity.getComponent<Shaped>(COMPONENT_TYPE_SHAPED);

    auto boundBox = shaped->getBoundingBox();
    auto width = boundBox.x;
    auto height = boundBox.y;

    auto sprited = entity.getComponent<Sprited>(COMPONENT_TYPE_SPRITED);
    s = renderer_->loadImg(sprited->getFilePath());
    // TODO apply clipping.

    t = renderer_->createTexture(*s);

    SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(t, 255);

    r->init(s, t);
  }
}

#endif
