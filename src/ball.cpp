
#include <memory>
#include <vector>

#include "lib/entity.h"
#include "lib/component.h"
#include "lib/positioning.h"

#include "moveable.h"

#include "ball.h"


Entity* createBall()
{
  std::vector<std::shared_ptr<Component>> components;
  std::shared_ptr<Moveable> moveable(new Moveable());
  components.push_back(moveable);
  Entity* ball = new Entity(components);

  return ball;
};
