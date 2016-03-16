
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>

#include <Box2D/Box2D.h>
#include "SDL2/SDL.h"

#include "lib/clock.h"
#include "lib/component.h"
#include "lib/entity.h"
#include "lib/manager.h"
#include "lib/sdl_renderer.h"
#include "lib/system.h"

#include "alias.h"

#include "c_boundable.h"
#include "c_evented.h"
#include "c_keyboardable.h"
#include "c_moveable.h"
#include "c_rectangular.h"
#include "c_painted.h"
#include "c_shaped.h"
#include "c_thrustable.h"
#include "c_universal.h"

#include "s_bound.h"
#include "s_keyboard_events.h"
#include "s_movement.h"
#include "s_rectangle_renderer.h"
#include "s_sdl_events.h"
#include "s_thrust.h"
#include "s_universe.h"

using namespace std;
using namespace aronnax;
using namespace spacegun;

const float TIMESTEP = 0.8;
const int WORLD_W = 640;
const int WORLD_H = 480;

const Color RED = Color(204, 0, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(246, 255, 0, 255);

const float THRUST_FACTOR = 1000;

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
}

Entity* setupBaseEntity(Vector2d initP, Vector2d initV, float w, float h,
    Color c, World& world)
{
  Vector2d bounds = Vector2d(WORLD_W, WORLD_H);
  Moveable* moveable = new Moveable(initV, initP);
  Rectangular* rectangular = new Rectangular(w, h);
  Shaped<Rectangular>* shaped = new Shaped<Rectangular>(*rectangular);
  Boundable* boundable = new Boundable(bounds);
  Painted* painted = new Painted(c);
  Universal* universal = new Universal(world, TIMESTEP);

  moveable->setFriction(0.01);
  moveable->setRestitution(0.1);
  moveable->setDensity(1.0);

  auto entity = new Entity();
  entity->addComponent(moveable);
  entity->addComponent(rectangular);
  entity->addComponent(shaped);
  entity->addComponent(boundable);
  entity->addComponent(painted);
  entity->addComponent(universal);

  return entity;
}

Entity* setupPlayerEntity(Entity* e, map<string, Ev*>& keyMap)
{
  Evented* evented = new Evented();
  Keyboardable* keyboardable = new Keyboardable(EV_USER_MOVEMENT, keyMap);
  Thrustable* thrustable = new Thrustable(THRUST_FACTOR);

  e->addComponent(evented);
  e->addComponent(keyboardable);
  e->addComponent(thrustable);

  return e;
}

int main()
{
  using namespace std::placeholders;

  printf("initializing...\n");

  // SDL setup
  setupSDL();
  auto window = setupVideo(WORLD_W, WORLD_H);
  atexit(SDL_Quit);

  // aronnax setup
  Clock clock;
  SDLRenderer renderer = SDLRenderer(window);
  Manager manager = Manager(renderer);

  // test box2d setup
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);
  world.SetContinuousPhysics(true);

  // initial values
  Vector2d initVelA = { 10, 20 };
  Vector2d initVelB = { 90, 40 };
  Vector2d initPosA = { 10, 30 };
  Vector2d initPosB = { 500, 120 };
  Vector2d initPlayer = { 100, 40 };
  Vector2d initPlayerV = { 0, 0 };
  float initWA = 20;
  float initHA = 55;
  float initWB = 60;
  float initHB = 50;
  map<string, Ev*> keyMap;
  EvUserMovement up(Vector2d(0, -1));
  EvUserMovement right(Vector2d(1, 0));
  EvUserMovement down(Vector2d(0, 1));
  EvUserMovement left(Vector2d(-1, 0));

  keyMap["W"] = &up;
  keyMap["D"] = &right;
  keyMap["S"] = &down;
  keyMap["A"] = &left;

  // setup asteroids
  auto asteroidA = setupBaseEntity(initPosA, initVelA, initWA, initHA, RED,
      world);
  auto asteroidB = setupBaseEntity(initPosB, initVelB, initWB, initHB, RED,
      world);
  auto base = setupBaseEntity(initPlayer, initPlayerV, initWB, initHB, YELLOW,
      world);
  auto ship = setupPlayerEntity(base, keyMap);

  // setup systems
  Bound bound;
  Events events;
  KeyboardEvents<EvUserMovement> keyboardEvents;
  Movement movement;
  RectangleRenderer rectangle(&renderer);
  Thrust thrust;
  Universe universe;;

  // setup to manager
  manager.addEntity(*asteroidA);
  manager.addEntity(*asteroidB);
  manager.addEntity(*ship);
  manager.addSystem(&bound);
  manager.addSystem(&events);
  manager.addSystem(&keyboardEvents);
  manager.addSystem(&movement);
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
