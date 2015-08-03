
#include <vector>

#include "lib/entity.h"
#include "lib/component.h"
#include "lib/positioning.h"

#include "moveable.h"

#include "ball.h"

namespace game {

Entity* createBall()
{
  std::vector<Component*> components;
  Moveable* moveable = new Moveable();
  components.push_back(moveable);
  Entity* ball = new Entity(components);
  Vector2d velocity = (1, 2);
  moveable->init(ball, velocity);

  return ball;
};

}

