
#ifndef _h_Moveable
#define _h_Moveable

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

class Circlular : public aronnax::Component
{
  public:
    ~Circlular() {};
    void render(aronnax::Entity &entity);
};

}

#endif
