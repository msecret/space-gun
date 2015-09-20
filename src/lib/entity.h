
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <vector>

#include "component.h"
#include "units.h"
#include "renderer.h"

namespace aronnax {

class Entity
{
  public:
    Entity(std::vector<std::shared_ptr<Component>> components);
    Entity(std::vector<std::shared_ptr<Component>> components,
           std::shared_ptr<Renderer> renderer);
    ~Entity();
    void update(const uint32_t dt);
    void render(const uint32_t dt);
    Vector2d v;
    Vector2d pos;

  private:
    // TODO typedef replace all of these
    std::vector<std::shared_ptr<Component>> components_;
    std::shared_ptr<aronnax::Renderer> renderer_;

};

}

#endif
