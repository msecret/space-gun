
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

#include "c_boundable.h"
#include "c_damageable.h"
#include "c_evented.h"
#include "c_keyboardable.h"
#include "c_joint.h"
#include "c_mortal.h"
#include "c_moveable.h"
#include "c_notification.h"
#include "c_oriented.h"
#include "c_rectangular.h"
#include "c_rendered.h"
#include "c_painted.h"
#include "c_shaped.h"
#include "c_thrustable.h"
#include "c_universal.h"

#include "s_bound.h"
#include "s_damage.h"
#include "s_death.h"
#include "s_keyboard_events.h"
#include "s_impacts.h"
#include "s_movement.h"
#include "s_notify.h"
#include "s_rectangle_renderer.h"
#include "s_sdl_events.h"
#include "s_thrust.h"
#include "s_universe.h"

using namespace std;
using namespace aronnax;
using namespace spacegun;

const float TIMESTEP = 0.8;
const int WORLD_W = 1280;
const int WORLD_H = 960;

const Color RED = Color(135, 42, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(200, 220, 68, 255);
const Color BLUE = Color(0, 110, 255, 255);
const Color COL_SHIELD = Color(80, 200, 200, 175);

const float THRUST_FACTOR = 1700;

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
        vector<float> total;
        total = setupImpact(total, *impulse);
        EvImpact ev(total);
        entity->emit(EV_IMPACT, &ev);
      }
      if ( bodyUserDataB ) {
        auto entity = static_cast<Entity*>(bodyUserDataB);
        vector<float> total;
        total = setupImpact(total, *impulse);
        EvImpact ev(total);
        entity->emit(EV_IMPACT, &ev);
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
  Vector2d bounds = Vector2d(WORLD_W, WORLD_H);
  Moveable* moveable = new Moveable(initV, initP, randAngle);
  Rectangular* rectangular = new Rectangular(w, h);
  Shaped* shaped = new Shaped(*rectangular);
  Boundable* boundable = new Boundable(bounds);
  Rendered* rendered = new Rendered();
  Painted* painted = new Painted(c);
  Universal* universal = new Universal(world, TIMESTEP);

  moveable->setFriction(.0001f);
  moveable->setRestitution(0.80f);
  moveable->setDensity(8.0f);

  auto entity = new Entity();
  entity->addComponent(moveable);
  entity->addComponent(rectangular);
  entity->addComponent(shaped);
  entity->addComponent(boundable);
  entity->addComponent(painted);
  entity->addComponent(rendered);
  entity->addComponent(universal);

  return entity;
}

Entity* setupPlayerEntity(Entity* e, map<string, Ev*>& keyMap, string name)
{
  auto painted = e->getComponent<Painted>(COMPONENT_TYPE_PAINTED);
  auto moveable = e->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);

  auto col = painted->getColor();
  auto pos = moveable->getPos();

  Damageable* damageable = new Damageable(100);
  Evented* evented = new Evented();
  Keyboardable* keyboardable = new Keyboardable(keyMap);
  Mortal* mortal = new Mortal();
  Notification* notification = new Notification(pos, name, col);
  Oriented* oriented = new Oriented(*moveable);
  Thrustable* thrustable = new Thrustable(THRUST_FACTOR);

  damageable->setDamageFactor(0.001f);

  e->addComponent(damageable);
  e->addComponent(evented);
  e->addComponent(keyboardable);
  e->addComponent(mortal);
  e->addComponent(notification);
  e->addComponent(oriented);
  e->addComponent(thrustable);

  return e;
}

Entity* setupShieldEntity(Entity* e, Entity* ship)
{
  Joint* joint = new Joint(ship);
  Joint* jointB = new Joint(e, true);

  e->addComponent(joint);
  ship->addComponent(jointB);

  auto moveable = e->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
  moveable->setDensity(0.5f);

  return e;
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
  Vector2d initVelA = { 10, 20 };
  Vector2d initVelB = { 90, 40 };
  Vector2d initVelC = { .1, .3 };
  Vector2d initPosA = { 10, 30 };
  Vector2d initPosB = { 500, 120 };
  Vector2d initPosC = { 300, 400 };
  Vector2d initPlayer = { 100, 40 };
  Vector2d initPlayerV = { 0, 0 };
  float initWC = 80;
  float initHC = 50;
  map<string, Ev*> keyMap;
  map<string, Ev*> keyMapP2;
  EvUserMovement up(Vector2d(1, 1));
  EvUserMovement right(Vector2d(1, 0));
  EvUserMovement down(Vector2d(-1, -1));
  EvUserMovement left(Vector2d(-1, 0));
  EvUserRotation clockwise(1.0f);
  EvUserRotation counterClockwise(-1.0f);
  const unsigned int WEAPON_CLASS_BEAM = 1;
  EvWeaponFired beamWeapon(WEAPON_CLASS_BEAM);

  keyMap["W"] = &up;
  keyMap["D"] = &right;
  keyMap["S"] = &down;
  keyMap["A"] = &left;
  keyMap["E"] = &clockwise;
  keyMap["Q"] = &counterClockwise;
  keyMap["G"] = &beamWeapon;

  keyMapP2["Keypad 8"] = &up;
  keyMapP2["Keypad 6"] = &right;
  keyMapP2["Keypad 5"] = &down;
  keyMapP2["Keypad 4"] = &left;
  keyMapP2["Keypad 9"] = &clockwise;
  keyMapP2["Keypad 7"] = &counterClockwise;

  // setup asteroids
  auto asteroidA = setupBaseEntity(initPosA, initVelA, 10, 13, RED,
      world);
  auto asteroidB = setupBaseEntity(initPosB, initVelB, 15, 11, RED,
      world);
  auto asteroidC = setupBaseEntity(initPosC, initVelC, initWC, initHC, RED,
      world);
  auto asteroidD = setupBaseEntity(Vector2d(200, 200),
      Vector2d( -0.3, 0.2),
      25,
      28,
      RED,
      world);
  auto asteroidE = setupBaseEntity(Vector2d(250, 400),
      Vector2d( 0.5, -0.2),
      32,
      36,
      RED,
      world);
  auto asteroidF = setupBaseEntity(Vector2d(450, 300),
      Vector2d( -0.1, -0.3),
      42,
      43,
      RED,
      world);
  auto asteroidG = setupBaseEntity(Vector2d(250, 400),
      Vector2d( -0.1, -0.1),
      45,
      48,
      RED,
      world);
  auto asteroidH = setupBaseEntity(Vector2d(800, 600),
      Vector2d( -0.8, -0.1),
      30,
      30,
      RED,
      world);
  auto asteroidI = setupBaseEntity(Vector2d(600, 800),
      Vector2d( -0.5, -0.75),
      43,
      36,
      RED,
      world);
  auto asteroidJ = setupBaseEntity(Vector2d(800, 900),
      Vector2d( 1.2, -0.75),
      20,
      16,
      RED,
      world);
  auto asteroidK = setupBaseEntity(Vector2d(400, 900),
      Vector2d( -1.0, -0.4),
      20,
      16,
      RED,
      world);
  auto asteroidL = setupBaseEntity(Vector2d(1200, 300),
      Vector2d( 0.3, -1.4),
      45,
      30,
      RED,
      world);
  auto asteroidM = setupBaseEntity(Vector2d(1000, 500),
      Vector2d( 0.8, 1.1),
      9.0,
      13,
      RED,
      world);
  auto asteroidN = setupBaseEntity(Vector2d(600, 600),
      Vector2d( 1.4, 2.1),
      12,
      18,
      RED,
      world);
  auto asteroidO = setupBaseEntity(Vector2d(1000, 700),
      Vector2d( 1.2, -1.8),
      26,
      29,
      RED,
      world);
  auto asteroidP = setupBaseEntity(Vector2d(500, 500),
      Vector2d( -0.2, 1.4),
      25,
      25,
      RED,
      world);
  auto asteroidQ = setupBaseEntity(Vector2d(400, 700),
      Vector2d( 0.5, 0.3),
      27,
      29,
      RED,
      world);
  auto asteroidR = setupBaseEntity(Vector2d(200, 700),
      Vector2d( 0.2, -0.86),
      30,
      40,
      RED,
      world);
  auto asteroidS = setupBaseEntity(Vector2d(600, 900),
      Vector2d( 0.4, 0.8),
      15,
      18,
      RED,
      world);
  auto asteroidT = setupBaseEntity(Vector2d(800, 900),
      Vector2d( 1.1, -0.3),
      11,
      12,
      RED,
      world);
  auto base = setupBaseEntity(Vector2d(100, 100), initPlayerV, 50, 45, GREEN,
      world);
  auto baseP2 = setupBaseEntity(Vector2d(1100, 40), initPlayerV, 50, 45,
      BLUE, world);
  auto ship = setupPlayerEntity(base, keyMap, "PlayerA");
  auto shipP2 = setupPlayerEntity(baseP2, keyMapP2, "PlayerB");
  auto baseShield1 = setupBaseEntity(Vector2d(100, 100), initPlayerV, 35, 45,
      COL_SHIELD,  world);
  auto baseShield2 = setupBaseEntity(Vector2d(1100, 40), initPlayerV, 35, 45,
      COL_SHIELD,  world);
  auto shield1 = setupShieldEntity(baseShield1, ship);
  auto shield2 = setupShieldEntity(baseShield2, shipP2);

  // setup systems
  Bound bound;
  Death death;
  Damage damage;
  Events events;
  KeyboardEvents<EvUserMovement> keyboardEventsM;
  KeyboardEvents<EvUserRotation> keyboardEventsR;
  Impacts impacts;
  Movement movement;
  Notify notify(&renderer);
  RectangleRenderer rectangle(&renderer);
  Thrust thrust;
  Universe universe;;

  // setup to manager
  manager.addEntity(*asteroidA);
  manager.addEntity(*asteroidB);
  manager.addEntity(*asteroidC);
  manager.addEntity(*asteroidD);
  manager.addEntity(*asteroidE);
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
  manager.addEntity(*asteroidQ);
  manager.addEntity(*asteroidR);
  manager.addEntity(*asteroidS);
  manager.addEntity(*asteroidT);
  manager.addEntity(*ship);
  manager.addEntity(*shipP2);
  manager.addEntity(*shield1);
  manager.addEntity(*shield2);
  manager.addSystem(&bound);
  manager.addSystem(&damage);
  manager.addSystem(&impacts);
  manager.addSystem(&death);
  manager.addSystem(&events);
  manager.addSystem(&keyboardEventsM);
  manager.addSystem(&keyboardEventsR);
  manager.addSystem(&movement);
  manager.addSystem(&notify);
  manager.addSystem(&rectangle);
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
