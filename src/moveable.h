
#ifndef _h_Moveable
#define _h_Moveable

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

class Moveable : public aronnax::Component
{
  public:
    void update(aronnax::Entity &entity, const uint32_t dt);
};

}

#endif
