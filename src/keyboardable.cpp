
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

Keyboardable::Keyboardable(aronnax::Entity &entity)
{
  entity.on(EV_KEYBOARD, [&](SDL_KeyboardEvent ev) {
    printKey(&ev);
  });
}

void Keyboardable::update(aronnax::Entity &entity, const uint32_t dt)
{
}

void Keyboardable::printKey(SDL_KeyboardEvent *key)
{
  printf("print key");
  if( key->type == SDL_KEYUP )
    printf( "Release:- " );
  else
    printf( "Press:- " );

  printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
}

std::string Keyboardable::getType()
{
  return "Keyboardable";
}


}
