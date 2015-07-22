
#include <vector>

#include "lib/entity.h"
#include "lib/component.h"
#include "lib/sdl_renderer.h"


Entity* createBall()
{
  std::vector<Component*> components;
  return new Entity(new SDLRenderer(),
                    components);
}
