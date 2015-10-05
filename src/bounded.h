
#ifndef _h_Bounded
#define _h_Bounded

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

class Bounded : public aronnax::Component
{
  public:
    void update(aronnax::Entity &entity, const uint32_t dt);
    std::string getType();
  private:
    double wrapAround(double coordinate, double max);
};

}

#endif
