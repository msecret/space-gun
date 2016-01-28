
#ifndef _h_Collidable
#define _h_Collidable

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

typedef struct Collision {
  aronnax::Entity &entityA;
  aronnax::Entity &entityB;
  Vector2d &pos;
}

class Collidable : public aronnax::Component
{
  public:
    void update(aronnax::Entity &entity, const uint32_t dt);
    void update(aronnax::Entity &entityA, aronnax::Entity &entityB, 
        const uint32_t dt);
    std::string getType();
};

}

#endif
