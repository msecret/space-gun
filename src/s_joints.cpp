
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "lib/units.h"

#include "c_joint.h"
#include "c_moveable.h"
#include "c_universal.h"
#include "s_joints.h"

namespace spacegun {
  using namespace std;

  using aronnax::EV_MOVE;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvMove;

  extern const string COMPONENT_TYPE_JOINT;

  void Joints::init(Entities& entities)
  {
    for (auto e : entities) {
      initEntity(*e);
    }
  }

  void Joints::onAddEntity(Entity& entity)
  {
    initEntity(entity);
  }

  void Joints::initEntity(Entity& entity)
  {
    auto c = entity.getComponent<Joint>(COMPONENT_TYPE_JOINT);
    auto u = entity.getComponent<Universal>(COMPONENT_TYPE_UNIVERSAL);

    auto world = u->getWorld();
    auto entityA = c->getEntityA();
    auto entityB = c->getEntityB();

    c->init(*world);
    bindEntity(*entityA, *entityB);
    bindEntity(*entityB, *entityA);
  }

  void Joints::bindEntity(Entity& parentEntity, Entity& childEntity)
  {
    using std::cout;
    using std::endl;

    cout << "bindEntity" << endl;
    cout << &parentEntity << endl;

    parentEntity.on(EV_MOVE, [&](EvMove* ev) {
      cout << "on ev move" << endl;

      if (childEntity.hasComponent(COMPONENT_TYPE_MOVEABLE)) {
        auto parentMoveable = parentEntity.getComponent<Moveable>(
            COMPONENT_TYPE_MOVEABLE);
        auto childMoveable = childEntity.getComponent<Moveable>(
            COMPONENT_TYPE_MOVEABLE);

        auto parentPos = parentMoveable->getPos();
        auto childPos = childMoveable->getPos();
        auto offset = parentPos - childPos;
        auto newPos = ev->getPos() + offset;

        childMoveable->setTransform(newPos);
      }
    });
  }

  const string& Joints::getType()
  {
    return COMPONENT_TYPE_JOINT;
  }

}
