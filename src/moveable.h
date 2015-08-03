
#ifndef _h_Moveable
#define _h_Moveable

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/positioning.h"

class Moveable : public Component
{
  public:
    Moveable(Entity* entity, const Vector2d & v);
    ~Moveable();
    void receive(int message);
    void update(Entity* entity, int dt);

  private:
    Entity* entity_;
};

#endif
