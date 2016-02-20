
#include "lib/entity.h"
#include "lib/renderer.h"

#include "c_rectangular.h"
#include "s_rectangle_renderer.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_RECTANGULAR;

  RectangleRenderer::RectangleRenderer() 
  {
    renderer_ = nullptr;
  }

  RectangleRenderer::RectangleRenderer(IRenderer* renderer) :
    renderer_(renderer)
  { }

  void RectangleRenderer::render(const uint32_t dt, aronnax::Entities& entities)
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
      aronnax::Entity& entity)
  {
    if (renderer_ == nullptr) {
      // TODO this is techincally an error condition, what should be done?
      return;
    }

    auto c = entity.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);
    aronnax::Vector2d pos = entity.getPos();
    aronnax::Vector2d box = { c->getW(), c->getH() };

    renderer_->drawRectangle(pos, box);
  }
}
