
#include <cstdio>
#include <iostream>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "lib/clock.h"
#include "lib/component.h"
#include "lib/entity.h"
#include "lib/manager.h"
#include "lib/sdl_renderer.h"
#include "lib/system.h"

#include "alias.h"
#include "constants.h"

#include "c_boundable.h"
#include "c_damageable.h"
#include "c_evented.h"
#include "c_keyboardable.h"
#include "c_joint.h"
#include "c_joint_prismatic.h"
#include "c_joint_solid.h"
#include "c_mortal.h"
#include "c_moveable.h"
#include "c_notification.h"
#include "c_oriented.h"
#include "c_rectangular.h"
#include "c_rendered.h"
#include "c_painted.h"
#include "c_shaped.h"
#include "c_smasher.h"
#include "c_sprited.h"
#include "c_thrustable.h"
#include "c_universal.h"

#include "s_bound.h"
#include "s_damage.h"
#include "s_death.h"
#include "s_keyboard_events.h"
#include "s_joints.h"
#include "s_impacts.h"
#include "s_movement.h"
#include "s_notify.h"
#include "s_paint_renderer.h"
#include "s_sdl_events.h"
#include "s_sprite_renderer.h"
#include "s_thrust.h"
#include "s_universe.h"

using namespace std;
using namespace aronnax;
using namespace spacegun;

const float TIMESTEP = 0.8;
const int WORLD_W = 1280;
const int WORLD_H = 960;

const Color BLUE = Color(0, 110, 255, 255);
const Color GREEN = Color(171, 210, 23, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color SHIP = Color(0.0f, 0.0f, 0.0f, 0.0f);
const Color COL_SHIELD = Color(80, 200, 200, 0);
int playerI = 0;

const float THRUST_FACTOR = 0.75;

Color randomGray() {
  auto r = rand() % 210;
  Color color(r, r, r, 255);
  return color;
}


class CollisionListener : public b2ContactListener
{
  public:
    void PostSolve(b2Contact*  contact,
        const b2ContactImpulse*  impulse)
    {
      void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
      void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserDataA ) {
        auto entity = static_cast<Entity*>(bodyUserDataA);
        if (entity->hasComponent(COMPONENT_TYPE_DAMAGEABLE)) {
          vector<float> total;
          total = setupImpact(total, *impulse);
          EvImpact ev(total);
          entity->emit(EV_IMPACT, &ev);
        }
      }
      if ( bodyUserDataB ) {
        auto entity = static_cast<Entity*>(bodyUserDataB);
        if (entity->hasComponent(COMPONENT_TYPE_DAMAGEABLE)) {
          vector<float> total;
          total = setupImpact(total, *impulse);
          EvImpact ev(total);
          entity->emit(EV_IMPACT, &ev);
        }
      }
    }

  private:
    vector<float> setupImpact(vector<float>& t, const b2ContactImpulse& impulse)
    {
      auto normalImpulses = impulse.normalImpulses;
      for(unsigned int i = 0; i < sizeof(normalImpulses); i=i+1) {
        t.push_back(normalImpulses[i]);
      }

      return t;
    }
};

SDL_Window* setupVideo(int worldW, int worldH)
{
  return SDL_CreateWindow("Maximized text",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      worldW,
                                      worldH,
                                      SDL_WINDOW_RESIZABLE);
}

void setupSDL()
{
  int retval = SDL_Init(SDL_INIT_EVERYTHING);
  if (retval)
  {
      printf("SDL_Init: Couldn't start SDL\n");
      printf("%s\n", SDL_GetError());
  }
  if (TTF_Init() != 0) {
    cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
    SDL_Quit();
    exit(1);
  }
}

Entity* setupBaseEntity(Vector2d initP, Vector2d initV, float w, float h,
    Color c, World& world)
{
  float randAngle = static_cast <float> (rand()) / (
      static_cast <float> (RAND_MAX/180.0));
  Vector2d bounds = Vector2d(WORLD_W / DRAW_FACTOR, WORLD_H / DRAW_FACTOR);
  Moveable* moveable = new Moveable(initV, initP, randAngle);
  Rectangular* rectangular = new Rectangular(w, h);
  Shaped* shaped = new Shaped(*rectangular);
  Boundable* boundable = new Boundable(bounds);
  Rendered* rendered = new Rendered();
  Universal* universal = new Universal(world, TIMESTEP);

  moveable->setFriction(.0001f);
  moveable->setRestitution(0.80f);
  moveable->setDensity(7.0f);

  auto entity = new Entity();
  entity->addComponent(moveable);
  entity->addComponent(rectangular);
  entity->addComponent(shaped);
  entity->addComponent(boundable);
  entity->addComponent(rendered);
  entity->addComponent(universal);

  if (c.a > 0) {
    Painted* painted = new Painted(c);
    entity->addComponent(painted);
  }

  return entity;
}

Entity* setupPlayerEntity(Entity* e, map<string, Ev*>& keyMap, string name)
{
  auto moveable = e->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);

  auto pos = moveable->getPos();
  pos.x = pos.x * 10;
  string imgName = "";
  if (playerI == 0) {
    imgName = "./img/osiri-v2-p1.png";
  } else {
    imgName = "./img/osiri-v2-p2.png";
  }

  Damageable* damageable = new Damageable(100);
  Evented* evented = new Evented();
  Keyboardable* keyboardable = new Keyboardable(keyMap);
  Mortal* mortal = new Mortal();
  Notification* notification = new Notification(pos, name, BLUE);
  Oriented* oriented = new Oriented(*moveable);
  Sprited* sprited = new Sprited(imgName);
  Thrustable* thrustable = new Thrustable(THRUST_FACTOR);

   playerI += 1;

  damageable->setDamageFactor(2.0f);

  e->addComponent(damageable);
  e->addComponent(evented);
  e->addComponent(keyboardable);
  e->addComponent(mortal);
  e->addComponent(notification);
  e->addComponent(oriented);
  e->addComponent(sprited);
  e->addComponent(thrustable);

  return e;
}

Entity* setupShieldEntity(Entity* shield, Entity* ship, Entity* joinerShield,
    World& world)
{
  JointMotor motor(0.15, -0.05);
  Sprited* sprited = new Sprited("./img/shield.png");
  auto pJoint = new JointPrismatic(ship, shield, &motor);
  auto cUniv = new Universal(world);

  pJoint->setRelativeAnchor(Vector2d(-4.0f, 0));
  pJoint->setTranslation(-2.5, 3.0);

  joinerShield->addComponent(pJoint);
  joinerShield->addComponent(cUniv);

  shield->addComponent(sprited);

  auto moveable = shield->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
  moveable->setDensity(0.01f);
  moveable->setFriction(1.0f);

  return shield;
}

Entity* setupBeamEntity(Entity* beam, Entity* ship, Entity* joinerBeam,
    World& world)
{
  auto pJoint = new JointSolid(ship, beam, 1.5708);
  auto cUniv = new Universal(world);

  pJoint->setRelativeAnchor(Vector2d(-2.7f, -3.1f));

  joinerBeam->addComponent(pJoint);
  joinerBeam->addComponent(cUniv);

  auto moveable = beam->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
  moveable->setDensity(0.001f);
  moveable->setFriction(1.0f);

  return beam;
}

Entity* setupWeaponEntity(Entity* weapon, Entity* ship) {
  // TODO change to player entity
  /*
  auto playerMoveable = playerEntity->getComponent<Moveable>(
      COMPONENT_TYPE_MOVEABLE);
  auto initP = playerMoveable->getPos();
  auto angle = playerMoveable->getAngle() + 90.0;
  */
  return weapon;
}

int main()
{
  using namespace std::placeholders;

  printf("initializing...\n");

  // SDL setup
  setupSDL();
  auto window = setupVideo(WORLD_W, WORLD_H);
  atexit(TTF_Quit);
  atexit(SDL_Quit);

  // aronnax setup
  Clock clock;
  SDLRenderer renderer = SDLRenderer(window);
  Manager manager = Manager(renderer);

  // test box2d setup
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);
  world.SetContinuousPhysics(true);
  CollisionListener collisionListener;
  world.SetContactListener(&collisionListener);

  // initial values
  Vector2d initVelA = { 0.1, 0.2 };
  Vector2d initVelB = { 0.4, 0.03 };
  Vector2d initVelC = { .01, .03 };
  Vector2d initPosA = { 1, 3 };
  Vector2d initPosB = { 50, 12 };
  Vector2d initPosC = { 30, 40 };
  Vector2d initPlayer = { 10, 4 };
  Vector2d initPlayerV = { 0, 0 };
  float initWC = 8.0;
  float initHC = 5.0;
  map<string, Ev*> keyMap;
  map<string, Ev*> keyMapP2;
  EvUserMovement up(Vector2d(1, 1));
  EvUserMovement right(Vector2d(1, 0));
  EvUserMovement down(Vector2d(-1, -1));
  EvUserMovement left(Vector2d(-1, 0));
  EvUserRotation clockwise(1.0f);
  EvUserRotation counterClockwise(-1.0f);

  keyMap["W"] = &up;
  keyMap["D"] = &right;
  keyMap["S"] = &down;
  keyMap["A"] = &left;
  keyMap["E"] = &clockwise;
  keyMap["Q"] = &counterClockwise;

  keyMapP2["I"] = &up;
  keyMapP2["L"] = &right;
  keyMapP2["K"] = &down;
  keyMapP2["J"] = &left;
  keyMapP2["O"] = &clockwise;
  keyMapP2["U"] = &counterClockwise;

  // setup asteroids
  auto asteroidA = setupBaseEntity(initPosA, initVelA, 1, 1, randomGray(),
      world);
  auto asteroidB = setupBaseEntity(initPosB, initVelB, 1, 1, randomGray(),
      world);
  auto asteroidC = setupBaseEntity(initPosC, initVelC, initWC, initHC, randomGray(),
      world);
  auto asteroidD = setupBaseEntity(Vector2d(20, 20),
      Vector2d( -0.09, 0.02),
      2.5,
      2.8,
      randomGray(),
      world);
  auto asteroidE = setupBaseEntity(Vector2d(25, 40),
      Vector2d( 0.05, -0.02),
      3.2,
      3.6,
      randomGray(),
      world);
  auto asteroidF = setupBaseEntity(Vector2d(45, 30),
      Vector2d( -0.1, -0.3),
      4.2,
      4.3,
      randomGray(),
      world);
  auto asteroidG = setupBaseEntity(Vector2d(25, 40),
      Vector2d( -0.01, -0.01),
      4.5,
      4.8,
      randomGray(),
      world);
  auto asteroidH = setupBaseEntity(Vector2d(80, 60),
      Vector2d( -0.08, -0.01),
      3.0,
      3.0,
      randomGray(),
      world);
  auto asteroidI = setupBaseEntity(Vector2d(60, 80),
      Vector2d( -0.05, -0.075),
      4.3,
      3.6,
      randomGray(),
      world);
  auto asteroidJ = setupBaseEntity(Vector2d(80, 90),
      Vector2d( .12, -0.075),
      2.0,
      1.6,
      randomGray(),
      world);
  auto asteroidK = setupBaseEntity(Vector2d(40, 90),
      Vector2d( -.010, -0.04),
      2.0,
      1.6,
      randomGray(),
      world);
  auto asteroidL = setupBaseEntity(Vector2d(120, 30),
      Vector2d( 0.03, -.14),
      4.5,
      3.0,
      randomGray(),
      world);
  auto asteroidM = setupBaseEntity(Vector2d(100, 50),
      Vector2d( 0.08, .11),
      1.9,
      1.3,
      randomGray(),
      world);
  auto asteroidN = setupBaseEntity(Vector2d(60, 60),
      Vector2d( 0.14, 0.021),
      1.2,
      1.8,
      randomGray(),
      world);
  auto asteroidO = setupBaseEntity(Vector2d(100, 70),
      Vector2d( 0.012, -0.18),
      2.6,
      2.9,
      randomGray(),
      world);
  auto asteroidP = setupBaseEntity(Vector2d(50, 50),
      Vector2d( -0.02, 0.014),
      2.5,
      2.5,
      randomGray(),
      world);
  auto asteroidS = setupBaseEntity(Vector2d(60, 90),
      Vector2d( 0.04, 0.08),
      1.5,
      1.8,
      randomGray(),
      world);
  auto asteroidT = setupBaseEntity(Vector2d(80, 90),
      Vector2d( 0.011, -0.03),
      1.1,
      1.2,
      randomGray(),
      world);
  auto base = setupBaseEntity(Vector2d(10, 10), initPlayerV, 6, 4.235, SHIP,
      world);
  auto baseP2 = setupBaseEntity(Vector2d(110, 4), initPlayerV, 6, 4.235,
      SHIP, world);
  auto ship = setupPlayerEntity(base, keyMap, "PlayerA");
  auto shipP2 = setupPlayerEntity(baseP2, keyMapP2, "PlayerB");

  // Setup shield
  auto joinerShieldP1 = new Entity();
  auto joinerShieldP2 = new Entity();
  auto baseShieldP1 = setupBaseEntity(Vector2d(10, 10), initPlayerV, 3.5, 4.5,
      COL_SHIELD,  world);
  auto baseShieldP2 = setupBaseEntity(Vector2d(110, 10), initPlayerV, 3.5, 4.5,
      COL_SHIELD,  world);
  auto shieldP1 = setupShieldEntity(baseShieldP1, ship, joinerShieldP1, world);
  auto shieldP2 = setupShieldEntity(baseShieldP2, shipP2, joinerShieldP2, world);

  // Setup beams
  auto joinerBeamP1 = new Entity();
  auto baseBeamP1 = setupBaseEntity(Vector2d(10, 10),
    initPlayerV, 6, 1, GREEN, world);
  auto beamP1 = setupBeamEntity(baseBeamP1, ship, joinerBeamP1, world);

  // Setup weapon
  //auto joinerA = new Entity();
  //auto weaponBaseP1 = setupBaseEntity(Vector2d(100 + 25, 100 + 45),
  //    initPlayerV, 60, 5, GREEN, world);
  //auto weaponP1 = setupWeaponEntity(weaponBaseP1, ship);


  // setup systems
  Bound bound;
  Death death;
  Damage damage;
  Events events;
  KeyboardEvents<EvUserMovement> keyboardEventsM;
  KeyboardEvents<EvUserRotation> keyboardEventsR;
  Joints joints;
  Impacts impacts;
  Movement movement;
  Notify notify(&renderer);
  PaintRenderer<SDLRenderer> paintedRenderer(&renderer);
  SpriteRenderer<SDLRenderer> spriteRenderer(&renderer);
  Thrust thrust;
  Universe universe;;

  // setup to manager
  manager.addEntity(*asteroidA);
  manager.addEntity(*asteroidB);
  manager.addEntity(*asteroidD);
  manager.addEntity(*asteroidE);
  manager.addEntity(*asteroidC);
  manager.addEntity(*asteroidF);
  manager.addEntity(*asteroidG);
  manager.addEntity(*asteroidH);
  manager.addEntity(*asteroidI);
  manager.addEntity(*asteroidJ);
  manager.addEntity(*asteroidK);
  manager.addEntity(*asteroidL);
  manager.addEntity(*asteroidM);
  manager.addEntity(*asteroidN);
  manager.addEntity(*asteroidO);
  manager.addEntity(*asteroidP);
  //manager.addEntity(*asteroidQ);
  //manager.addEntity(*asteroidR);
  manager.addEntity(*asteroidS);
  manager.addEntity(*asteroidT);
  manager.addEntity(*ship);
  manager.addEntity(*shipP2);
  manager.addEntity(*joinerShieldP1);
  manager.addEntity(*shieldP1);
  manager.addEntity(*joinerShieldP2);
  manager.addEntity(*shieldP2);
  //manager.addEntity(*weaponP1);
  //manager.addEntity(*joinerA);
  manager.addEntity(*joinerBeamP1);
  manager.addEntity(*beamP1);
  //
  manager.addSystem(&bound);
  manager.addSystem(&damage);
  manager.addSystem(&impacts);
  manager.addSystem(&death);
  manager.addSystem(&events);
  manager.addSystem(&keyboardEventsM);
  manager.addSystem(&keyboardEventsR);
  manager.addSystem(&movement);
  // Note: joints has to be placed after movement because requires the body
  // to be initialized.
  manager.addSystem(&joints);
  manager.addSystem(&notify);
  manager.addSystem(&paintedRenderer);
  manager.addSystem(&spriteRenderer);
  manager.addSystem(&thrust);
  manager.addSystem(&universe);

  // clock manager
  function<void(const uint32_t)> f_update = bind(
      &Manager::update, &manager, _1);
  function<void(const uint32_t)> f_render = bind(
      &Manager::render, &manager, _1);
  clock.onConstantly(f_update);
  clock.onEveryFrame(f_render);
  clock.start();

  // TODO dlete pointers
  // for each entity
  //   for each component
  //     delete component
  //   delete entity

  return 0;
}
