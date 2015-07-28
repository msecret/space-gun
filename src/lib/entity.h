
#ifndef _h_Entity
#define _h_Entity

#include <vector>

#include "component.h"
#include "positioning.h"
#include "renderer.h"


class Entity
{
  public:
    Entity(std::vector<Component*> components);
    void update(int dt);
    void render();
    Vector2d v;
    Vector2d pos;

  private:
    std::vector<Component*> components_;

};

#endif
