
#include <vector>

#include "lib/entity.h"
#include "lib/component.h"


Entity* createBall()
{
  std::vector<Component*> components;
  return new Entity(components);
}
