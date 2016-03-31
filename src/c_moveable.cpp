
#include <Box2D/Box2D.h>

#include "./c_moveable.h"

namespace spacegun {
  using namespace std;
  using spacegun::MassData;

  extern const string COMPONENT_TYPE_MOVEABLE;

  Moveable::Moveable() :
    body_(nullptr),
    fixture_(nullptr),
    setMassData_(false)
  {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(0, 0);

    bodyDef_ = def;
    fixtureDef_.density = 1;
  }

  Moveable::Moveable(const Vector2d& initialVel,
           const Vector2d& initialPos) :
    body_(nullptr),
    fixture_(nullptr),
    setMassData_(false)
  {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(initialPos.x, initialPos.y);
    def.linearVelocity.Set(initialVel.x, initialVel.y);

    bodyDef_ = def;
    fixtureDef_.density = 1;
  };

  Moveable::Moveable(const Vector2d& initialVel,
           const Vector2d& initialPos, float initialAngle) :
    body_(nullptr),
    fixture_(nullptr),
    setMassData_(false)
  {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(initialPos.x, initialPos.y);
    def.linearVelocity.Set(initialVel.x, initialVel.y);
    def.angle = initialAngle;

    bodyDef_ = def;
    fixtureDef_.density = 1;
  };

  void Moveable::init(World& world, Shape& shape)
  {
    body_ = world.CreateBody(&bodyDef_);
    fixtureDef_.shape = &shape;
    fixture_ = body_->CreateFixture(&fixtureDef_);
    body_->SetLinearDamping(0.0f);
    if (setMassData_) {
      body_->SetMassData(&massData_);
    }
  }

  void Moveable::setDamageable()
  {
    body_->SetUserData(this);
  }

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

  float Moveable::getAngle()
  {
    if (body_) {
      return body_->GetAngle();
    }
    return bodyDef_.angle;
  }

  float Moveable::getFriction()
  {
    if (fixture_) {
      return fixture_->GetFriction();
    }
    return fixtureDef_.friction;
  }

  void Moveable::setFriction(float friction)
  {
    if (fixture_) {
      fixture_->SetFriction(friction);
    }
    fixtureDef_.friction = friction;
  }

  float Moveable::getRestitution()
  {
    if (fixture_) {
      return fixture_->GetRestitution();
    }
    return fixtureDef_.restitution;
  }

  void Moveable::setRestitution(float restitution)
  {
    if (fixture_) {
      fixture_->SetRestitution(restitution);
    }
    fixtureDef_.restitution = restitution;
  }

  float Moveable::getDensity()
  {
    if (fixture_) {
      return fixture_->GetDensity();
    }
    return fixtureDef_.density;
  }

  void Moveable::setDensity(float density)
  {
    if (fixture_) {
      fixture_->SetDensity(density);
    }
    fixtureDef_.density = density;
  }

  float Moveable::getMass()
  {
    if (body_) {
      return body_->GetMass();
    }
    return massData_.mass;
  }

  void Moveable::setMass(float mass, const Vector2d& center, float inertia)
  {
    massData_.mass = mass;
    massData_.center = center;
    massData_.I = inertia;
    setMassData_ = true;

    if (body_) {
      body_->SetMassData(&massData_);
    }
  }

  void Moveable::applyForce(const Vector2d& v)
  {
    body_->ApplyForceToCenter(v, true);
  }

  void Moveable::applyTorque(float torque)
  {
    body_->ApplyTorque(torque, true);
  }

  Body* Moveable::getBody()
  {
    return body_;
  }
}
