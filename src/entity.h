
#ifndef _h_Entity
#define _h_Entity

#include <vector>

#include "component/component.h"
#include "renderer.h"


class Entity
{
  public:
    Entity(Renderer* renderer, std::vector<Component*> components);
    void update(int dt);
    void render();

  private:
    Renderer* renderer_;
    std::vector<Component*> components_;

};

#endif
