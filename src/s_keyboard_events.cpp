
#include <algorithm>

#include "SDL2/SDL.h"

#include "lib/units.h"
#include "c_keyboardable.h"
#include "s_keyboard_events.h"
#include "s_sdl_events.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;

  void KeyboardEvents::init(aronnax::Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void KeyboardEvents::onAddEntity(aronnax::Entity& entity)
  {
    bindEntity(entity);
  }

  void KeyboardEvents::bindEntity(aronnax::Entity& entity)
  {
    entity.on(aronnax::EV_KEY, [&](const aronnax::EvKeyboard& ev) {
      handleKeys(ev, entity);
    });
  }

  void KeyboardEvents::handleKeys(const aronnax::EvKeyboard& ev,
      aronnax::Entity& entity)
  {
    auto c = entity.getComponent<Keyboardable>(COMPONENT_TYPE_KEYBOARDABLE);
    auto boundKeys = c->getKeys();
    auto keyName = ev.key;
    // TODO this has to be checked for every key, is it too slow?
    if (find(boundKeys.begin(), boundKeys.end(), keyName) != boundKeys.end()) {
      auto action = c->getAction(keyName);
      // TODO this won't allow to bind to one main event like EV_MOVEMENT.
      entity.emit(action, ev);
    }
  }

  const string& KeyboardEvents::getType()
  {
    return COMPONENT_TYPE_KEYBOARDABLE;
  }
}
