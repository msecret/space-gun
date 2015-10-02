
#include <cstdint>
#include <iostream>
#include <string>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "keyboardable.h"

namespace spacegun {

void Keyboardable::update(aronnax::Entity &entity, const uint32_t dt)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    printf("poll");
    switch(event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        printKey(&event.key);
        break;

      default:
          break;
    }
  }
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
