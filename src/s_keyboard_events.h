
#ifndef _h_KeyboardEvents
#define _h_KeyboardEvents

#include <cstdint>

#include "SDL2/SDL.h"

#include "lib/entity.h"
#include "lib/units.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  template <class TEvent>
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

  template <class TEvent>
  void KeyboardEvents<TEvent>::handleKeys(const aronnax::EvKeyboard& ev,
      aronnax::Entity& entity)
  {
    auto c = entity.getComponent<Keyboardable>(COMPONENT_TYPE_KEYBOARDABLE);
    auto boundKeys = c->getKeys();
    auto keyName = ev.key;
    // TODO this has to be checked for every key, is it too slow?
    if (find(boundKeys.begin(), boundKeys.end(), keyName) != boundKeys.end()) {
      auto action = c->getAction(keyName);
      const TEvent* castedAction = static_cast<const TEvent*>(action);
      auto eventCode = c->getEventCode();
      entity.emit(eventCode, castedAction);
    }

  }
}

#endif
