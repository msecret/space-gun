
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_moveable.h"
#include "../c_rectangular.h"
#include "../c_shaped.h"
#include "../c_universal.h"
#include "../s_movement.h"

using aronnax::Entity;
using aronnax::Vector2d;
using spacegun::Moveable;
using spacegun::Shaped;
using namespace spacegun;
using ::testing::_;

class TestBody {
  public:
    MOCK_METHOD1(ApplyForceToCenter, void(const Vector2d& v));
};

using Body = TestBody;

TEST(Moveable, constructor) {
  Vector2d expectedVel = { 2, 3 };
  Vector2d expectedPos = { 10, 20 };
  spacegun::Moveable c = spacegun::Moveable(expectedVel, expectedPos);

  auto actualVel = c.getVel();
  auto actualPos = c.getPos();

  EXPECT_EQ(actualVel, expectedVel);
  EXPECT_EQ(actualPos, expectedPos);
}

TEST(Moveable, angleConstructor) {
  Vector2d expectedVel = { 20, 3 };
  Vector2d expectedPos = { 15, 20 };
  float expectedAngle = 38.2;
  Moveable c(expectedVel, expectedPos, expectedAngle);

  auto actual = c.getAngle();

  EXPECT_EQ(actual, expectedAngle);
}

TEST(Moveable, init) {
  Vector2d g = { 0, 0 };
  World w(g);
  PolygonShape p;
  p.SetAsBox(2, 1);
  Moveable c;
  Entity e;

  c.init(w, p, e);

  auto actual = c.getBody();

  EXPECT_NE(actual, nullptr);
}

TEST(Moveable, getsetVel) {
  Vector2d expectedVel = { 2, 5 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setVel(expectedVel);
  auto actualVel = c.getVel();

  EXPECT_EQ(expectedVel.x, actualVel.x);
  EXPECT_EQ(expectedVel.y, actualVel.y);
}

TEST(Moveable, getsetPos) {
  Vector2d expectedPos = { 3, 5 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setPos(expectedPos);
  auto actual = c.getPos();

  EXPECT_EQ(expectedPos, actual);
}

TEST(Moveable, movePos) {
  Vector2d vel = { 1, 1 };
  Vector2d initPos = { 1, 1 };
  spacegun::Moveable c = spacegun::Moveable();

  c.setPos(initPos);
  c.move(vel);
  auto actual = c.getPos();

  EXPECT_EQ(actual, initPos + vel);
}

TEST(Moveable, getAngle) {
  Vector2d g = { 0.0, 0.0 };
  Vector2d vel = { 1, 1 };
  Vector2d initPos = { 1, 1 };
  float expectedAngle = 89.3;
  World w(g);
  PolygonShape p;
  p.SetAsBox(2, 1);
  Entity e;

  Moveable c = Moveable(vel, initPos, expectedAngle);

  auto actual = c.getAngle();
  EXPECT_EQ(actual, expectedAngle);

  c.init(w, p, e);

  actual = c.getAngle();
  EXPECT_EQ(actual, expectedAngle);
}

TEST(Moveable, getsetFriction) {
  float expected = 8.2;
  spacegun::Moveable c = spacegun::Moveable();

  c.setFriction(expected);

  auto actual = c.getFriction();

  EXPECT_EQ(actual, expected);
}

TEST(Moveable, getsetRestitution) {
  float expected = 8.3;
  spacegun::Moveable c = spacegun::Moveable();

  c.setRestitution(expected);

  auto actual = c.getRestitution();

  EXPECT_EQ(actual, expected);
}

TEST(Moveable, getsetDensity) {
  float expected = 8.4;
  spacegun::Moveable c = spacegun::Moveable();

  c.setDensity(expected);
}

TEST(Moveable, getsetMass) {
  Moveable c;
  float expectedMass = 4.5;
  Vector2d expectedCenter = { 1, 1 };

  c.setMass(expectedMass,
      expectedCenter,
      0);

  auto actual = c.getMass();

  EXPECT_EQ(actual, expectedMass);

  Vector2d g = { 0.0, 0.0 };
  World w(g);
  PolygonShape p;
  p.SetAsBox(2, 1);
  Entity e;

  c.init(w, p, e);

  actual = c.getMass();

  EXPECT_EQ(actual, expectedMass);
}

TEST(Movement, getType) {
  spacegun::Moveable c;
  EXPECT_EQ(spacegun::COMPONENT_TYPE_MOVEABLE, c.getType());
}

TEST(Movement, onAddEntity) {
  Vector2d g = { 0.0, 0.0 };
  Entity* e = new Entity();
  World w(g);

  Moveable m;
  Rectangular r(10.0, 20.0);
  Shaped s(r);
  Universal u(w);

  e->addComponent(&m);
  e->addComponent(&r);
  e->addComponent(&s);
  e->addComponent(&u);

  Movement sys;

  sys.onAddEntity(*e);

  auto actualBody = m.getBody();
  auto actualFixture = m.getBody();

  EXPECT_NE(actualBody, nullptr);
  EXPECT_NE(actualFixture, nullptr);

  delete e;
}

TEST(Moveable, applyForce) {
  Vector2d g = { 0.0, 0.0 };
  Vector2d initV = { 1.0, 1.0 };
  Vector2d initP = { 0.0, 0.0 };
  Vector2d force = { 4.0, 0.0 };
  World w(g);
  PolygonShape p;
  p.SetAsBox(2, 1);

  Moveable m(initV, initP);
  Entity e;

  m.init(w, p, e);

  auto actual = m.getVel();

  EXPECT_EQ(actual, initV);

  m.applyForce(force);
  w.Step(0.8, 8, 2);

  actual = m.getVel();

  // Note: 1.4 value found through trial.
  EXPECT_EQ(actual.x, 1.4f);
  EXPECT_EQ(actual.y, 1);
}
