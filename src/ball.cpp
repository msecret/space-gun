
#include <memory>
#include <vector>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

#include "ball.h"

#include "moveable.h"

namespace spacegun {

aronnax::Entity* createBall()
{
  std::vector<std::shared_ptr<aronnax::Component>> components;
  std::shared_ptr<Moveable> moveable(new Moveable());
  components.push_back(moveable);
  aronnax::Entity* ball = new aronnax::Entity(components);

  return ball;
};

}
