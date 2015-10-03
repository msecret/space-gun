
#ifndef _h_Circle
#define _h_Circle

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

class Circular : public aronnax::Component
{
  public:
    Circular() {};
    void render(aronnax::Entity &entity);
    std::string getType();
};

}

#endif
