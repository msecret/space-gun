
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <vector>

#include "component.h"
#include "positioning.h"
#include "renderer.h"

namespace aronnax {

class Entity
{
  public:
    Entity(std::vector<std::shared_ptr<Component>> components);
    ~Entity();
    void update(const int dt);
    void render();
    Vector2d v;
    Vector2d pos;

  private:
    std::vector<std::shared_ptr<Component>> components_;

};

}

#endif
