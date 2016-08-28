
#include "lib/units.h"
#include "c_joint.h"
#include "c_moveable.h"
#include "c_universal.h"
#include "s_joints.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_JOINT;

  void Joints::init(aronnax::Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void Joints::onAddEntity(aronnax::Entity& entity)
  {
    bindEntity(entity);
  }

  void Joints::bindEntity(aronnax::Entity& entity)
  {
    auto c = entity.getComponent<Joint>(COMPONENT_TYPE_JOINT);
    auto u = entity.getComponent<Universal>(COMPONENT_TYPE_UNIVERSAL);

    auto world = u->getWorld();

    c->init(*world);
  }

  const string& Joints::getType()
  {
    return COMPONENT_TYPE_JOINT;
  }

}
