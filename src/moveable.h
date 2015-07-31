
#ifndef _h_Moveable
#define _h_Moveable

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/positioning.h"

class Moveable : public Component
{
  public:
    Moveable();
    ~Moveable();
    void init(Entity* entity, Vector2d v);
    void receive(int message);
    void update(Entity* entity, int dt);
};

#endif
