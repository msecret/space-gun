
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
    void init(aronnax::Entity &entity);
    void init(aronnax::IEntity &entity);

  private:
    void handleKeys(SDL_KeyboardEvent *key, aronnax::Entity &entity);
    void handleKeys(SDL_KeyboardEvent *key, aronnax::IEntity &entity);
};

}

#endif
