
#include <cstdint>

#include "SDL2/SDL.h"
#include "lib/entity.h"

#include "c_evented.h"
#include "s_movement.h"
#include "s_sdl_events.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_EVENTED;
  extern const unsigned int EV_KEY;

  const string& Events::getType()
  {
    return COMPONENT_TYPE_EVENTED;
  }

  void Events::update(const uint32_t dt, aronnax::Entities& entities)
  {
    this->poll(dt, entities);
  }

  void Events::poll(const uint32_t dt, aronnax::Entities& entities)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          SDL_Log("quit");
          exit(0);
          break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
          for (auto e : entities) {
            e->emit(EV_KEY, &event);
          }
          break;

        default:
            break;
      }
    }
  }
}
