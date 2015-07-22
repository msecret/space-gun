
#ifndef _h_Moveable
#define _h_Moveable

#include "../lib/component.h"

class Moveable : Component
{
  public:
    Moveable() {};
    void update(Entity* entity, int dt);

}

#endif
