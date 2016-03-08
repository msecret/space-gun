
#include <Box2D/Box2D.h>

#include "./c_moveable.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_MOVEABLE;

  Moveable::Moveable() :
    body_(nullptr)
  {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(0, 0);

    bodyDef_ = def;
  }

  Moveable::Moveable(const Vector2d& initialVel,
           const Vector2d& initialPos) :
    body_(nullptr)
  {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(initialPos.x, initialPos.y);
    def.linearVelocity.Set(initialVel.x, initialVel.y);

    bodyDef_ = def;
  };

  const string Moveable::getType()
  {
    return COMPONENT_TYPE_MOVEABLE;
  }

  Vector2d Moveable::getVel()
  {
    if (body_) {
      return body_->GetLinearVelocity();
    }
    return bodyDef_.linearVelocity;
  }

  void Moveable::setVel(Vector2d newVel)
  {
    if (body_) {
      body_->SetLinearVelocity(newVel);
    }
    bodyDef_.linearVelocity = newVel;
  }

  Vector2d Moveable::getPos()
  {
    if (body_) {
      return body_->GetPosition();
    }
    return bodyDef_.position;
  }

  void Moveable::setPos(Vector2d newPos)
  {
    if (body_) {
      body_->SetTransform(newPos, body_->GetAngle());
    }
    bodyDef_.position = newPos;
  }

  void Moveable::move(Vector2d vel)
  {
    auto currentPos = getPos();
    auto newPos = currentPos + vel;
    if (body_) {
      body_->SetTransform(newPos, body_->GetAngle());
    }
    bodyDef_.position = newPos;
  }
}
