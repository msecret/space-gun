
#ifndef _h_Keyboardable
#define _h_Keyboardable

#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

namespace spacegun {

class Keyboardable : public aronnax::Component
{
  public:
    Keyboardable() {};
    void update(aronnax::Entity &entity, const uint32_t dt);
    std::string getType();

  private:
    void printKey(SDL_KeyboardEvent *key);
};

}

#endif
