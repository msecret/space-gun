
#include "lib/entity.h"
#include "lib/renderer.h"

#include "c_hideable.h"
#include "c_moveable.h"
#include "c_oriented.h"
#include "c_rectangular.h"
#include "c_rendered.h"
#include "c_painted.h"
#include "s_rectangle_renderer.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;

  extern const string COMPONENT_TYPE_RECTANGULAR;

  RectangleRenderer::RectangleRenderer()
  {
    renderer_ = nullptr;
  }

  RectangleRenderer::RectangleRenderer(IRenderer* renderer) :
    renderer_(renderer)
  { }

  void RectangleRenderer::init(Entities& entities)
  {
    for (auto e : entities) {
      initRectangle(*e);
    }
  }

  void RectangleRenderer::render(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->renderRectangle(dt, *e);
    }
  }

  const string& RectangleRenderer::getType()
  {
    return COMPONENT_TYPE_RECTANGULAR;
  }

  void RectangleRenderer::renderRectangle(const uint32_t dt,
      Entity& entity)
  {
    if (renderer_ == nullptr) {
      // TODO this is techincally an error condition, what should be done?
      return;
    }

    if (entity.hasComponent(COMPONENT_TYPE_HIDEABLE)) {
      auto hideable = entity.getComponent<Hideable>(COMPONENT_TYPE_HIDEABLE);
      if (hideable->getHidden()) return;
    }

    auto c = entity.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto rendered = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);
    Vector2d box = { c->getW(), c->getH() };
    Vector2d pos = moveable->getPos();
    auto texture = rendered->getTexture();
    auto angle = moveable->getAngle();

    renderer_->drawRectangle(pos, box, texture, angle);
  }

  void RectangleRenderer::initRectangle(Entity& entity)
  {
    SDL_Surface *s;
    SDL_Texture *t;
    auto c = entity.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);
    auto r = entity.getComponent<Rendered>(COMPONENT_TYPE_RENDERED);

    auto width = c->getW();
    auto height = c->getH();

    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    if (entity.hasComponent(COMPONENT_TYPE_PAINTED)) {
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
    }

    t = renderer_->createTexture(*s);
    // TODO fix duplicate if statement and getting of painted
    if (entity.hasComponent(COMPONENT_TYPE_PAINTED)) {
      auto p = entity.getComponent<Painted>(COMPONENT_TYPE_PAINTED);
      auto color = p->getColor();
      if (color.a < 255) {
        SDL_SetTextureAlphaMod(t, color.a);
        SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
      }
    }

    r->init(s, t);
  }
}
