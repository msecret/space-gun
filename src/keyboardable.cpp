
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
  if( key->type == SDL_KEYDOWN ) {
    std::string keyName = SDL_GetKeyName(key->keysym.sym);
    std::cout << "key: " << keyName << "\n";
    if (keyName == "A") {
      entity.v.x = -1;
      entity.v.y = 0;
    } else if (keyName == "S"){
      entity.v.x = 0;
      entity.v.y = 1;
    } else if (keyName == "D"){
      entity.v.x = 1;
      entity.v.y = 0;
    } else if (keyName == "W"){
      entity.v.x = 0;
      entity.v.y = -1;
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
