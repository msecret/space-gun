

#include "lib/entity.h"
#include "lib/sdl_renderer.h"

#include "c_moveable.h"
#include "c_rendered.h"
#include "c_shaped.h"
#include "c_sprited.h"
#include "s_sdl_sprite_renderer.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;

  extern const string COMPONENT_TYPE_SPRITED;

  SDLSpriteRenderer::SDLSpriteRenderer()
  {
    renderer_ = nullptr;
  }

  SDLSpriteRenderer::SDLSpriteRenderer(SDLRenderer* renderer) :
    renderer_(renderer)
  { }

  void SDLSpriteRenderer::init(Entities& entities)
  {
    for (auto e : entities) {
      initSprite(*e);
    }
  }

  void SDLSpriteRenderer::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->renderSprite(dt, *e);
    }
  }

  const string& SDLSpriteRenderer::getType()
  {
    return COMPONENT_TYPE_SPRITED;
  }

  void SDLSpriteRenderer::renderSprite(const uint32_t dt,
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

  void SDLSpriteRenderer::initSprite(Entity& entity)
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

    r->init(s, t);
  }
}
