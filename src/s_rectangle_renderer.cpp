
#include "lib/entity.h"
#include "lib/renderer.h"

#include "c_moveable.h"
#include "c_rectangular.h"
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
      initRectangle(e);
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

    auto c = entity.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    Vector2d box = { c->getW(), c->getH() };
    Vector2d pos = moveable->getPos();

    Color color = { 0, 0, 0, 0 };
    if (entity.hasComponent(COMPONENT_TYPE_PAINTED)) {
      auto cb = entity.getComponent<Painted>(COMPONENT_TYPE_PAINTED);
      color = cb->getColor();
    }

    renderer_->drawRectangle(pos, box, color);
    // renderer->drawRectangle(pos, box, texture, angle);
  }

  void RectangleRenderer::initRectangle(Entity& e)
  {
    SDL_Surface *s;
    auto c = entity.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);

    auto width = c.getW();
    auto height = c.getH();

    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    if (entity.hasComponent(COMPONENT_TYPE_PAINTED)) {
      auto p = entity.getComponent<Painted>(COMPONENT_TYPE_PAINTED);
      auto color = p->getColor();
      SDL_FillRect(s, NULL, SDL_MapRGB(s->format,
            color.r,
            color.g,
            color.b;));
    }
  }
}
