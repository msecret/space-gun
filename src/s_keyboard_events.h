
#ifndef _h_KeyboardEvents
#define _h_KeyboardEvents

#include <cstdint>

#include "SDL2/SDL.h"

#include "lib/entity.h"
#include "lib/units.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  class KeyboardEvents: public aronnax::System
  {
    public:
      KeyboardEvents() {};
      void init(aronnax::Entities& entities);
      void update(const uint32_t dt, aronnax::Entities& entities) {};
      void render(const uint32_t dt, aronnax::Entities& entities) {};
      void onAddEntity(aronnax::Entity& entity);
      const string& getType();

    private:
      void bindEntity(aronnax::Entity& entity);
      void handleKeys(const aronnax::EvKeyboard& ev, aronnax::Entity& entity);
  };
}

#endif
