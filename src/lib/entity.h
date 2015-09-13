
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <vector>

#include "component.h"
#include "positioning.h"
#include "renderer.h"


class Entity
{
  public:
    // TODO use boost:shared_ptr to ensure components are freed.
    Entity(std::vector<std::shared_ptr<Component>> components);
    ~Entity();
    void update(int dt);
    void render();
    Vector2d v;
    Vector2d pos;

  private:
    std::vector<Component*> components_;

};

#endif
