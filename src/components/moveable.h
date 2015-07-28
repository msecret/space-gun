
#ifndef _h_Moveable
#define _h_Moveable

#include "../lib/component.h"

class Moveable : Component
{
  public:
    Moveable() { };
    void init(Entity* entity, Vector2d v);
    void update(Entity* entity, int dt);

};

#endif
