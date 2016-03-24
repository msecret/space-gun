
#include <algorithm>
#include <cstdio>

#include "SDL2/SDL.h"

#include "lib/units.h"
#include "c_keyboardable.h"
#include "s_keyboard_events.h"
#include "s_sdl_events.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;

  template <class TEvent>
  void KeyboardEvents<TEvent>::init(aronnax::Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  template <class TEvent>
  void KeyboardEvents<TEvent>::onAddEntity(aronnax::Entity& entity)
  {
    bindEntity(entity);
  }

  template <class TEvent>
  void KeyboardEvents<TEvent>::bindEntity(aronnax::Entity& entity)
  {
    entity.on(aronnax::EV_KEY, [&](aronnax::EvKeyboard* ev) {
      handleKeys(*ev, entity);
    });
  }

  template <class TEvent>
  const string& KeyboardEvents<TEvent>::getType()
  {
    return COMPONENT_TYPE_KEYBOARDABLE;
  }

  template class KeyboardEvents<aronnax::Ev>;
  template class KeyboardEvents<aronnax::EvUserMovement>;
  template class KeyboardEvents<aronnax::EvUserRotation>;
}
