
#include <cstdint>
#include <iostream>
#include <string>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/events.h"
#include "lib/units.h"
#include "keyboardable.h"

namespace spacegun {

void Keyboardable::init(aronnax::Entity &entity)
{
  entity.on(EV_KEYBOARD, [&](SDL_Event* ev) {
    handleKeys(&ev->key, entity);
  });
}

void Keyboardable::update(aronnax::Entity &entity, const uint32_t dt)
{
}

void Keyboardable::handleKeys(SDL_KeyboardEvent *key, aronnax::Entity &entity)
{
  const double thrust = 0.1;
  if( key->type == SDL_KEYDOWN ) {
    std::string keyName = SDL_GetKeyName(key->keysym.sym);
    std::cout << "key: " << keyName << "\n";
    if (keyName == "A") {
      entity.v.x += -(thrust);
    } else if (keyName == "S"){
      entity.v.y += thrust;
    } else if (keyName == "D"){
      entity.v.x += thrust;
    } else if (keyName == "W"){
      entity.v.y += -(thrust);
    } else {
      // Do nothing;
    }
  }
}

std::string Keyboardable::getType()
{
  return "Keyboardable";
}


}
