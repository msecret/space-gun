
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
#include "lib/units.h"

#include "c_boundable.h"
#include "c_evented.h"
#include "c_keyboardable.h"
#include "c_moveable.h"
#include "c_rectangular.h"
#include "c_painted.h"
#include "c_thrustable.h"

#include "s_bound.h"
#include "s_keyboard_events.h"
#include "s_movement.h"
#include "s_rectangle_renderer.h"
#include "s_sdl_events.h"
#include "s_thrust.h"

using namespace std;
using namespace aronnax;
using namespace spacegun;

const int WORLD_W = 640;
const int WORLD_H = 480;

const Color RED = Color(204, 0, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(246, 255, 0, 255);

const double THRUST_FACTOR = 0.1;

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

Entity* setupBaseEntity(Vector2d initP, Vector2d initV, double w, double h,
    Color c)
{
  Vector2d bounds = Vector2d(WORLD_W, WORLD_H);
  Moveable* moveable = new Moveable(initV);
  Rectangular* rectangular = new Rectangular(w, h);
  Boundable* boundable = new Boundable(bounds);
  Painted* painted = new Painted(c);

  auto entity = new Entity();
  entity->setPos(initP);
  entity->addComponent(moveable);
  entity->addComponent(rectangular);
  entity->addComponent(boundable);
  entity->addComponent(painted);

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

  // initial values
  Vector2d initVelA = { 1, 2 };
  Vector2d initVelB = { 3, 2 };
  Vector2d initPosA = { 30, 50 };
  Vector2d initPosB = { 20, 0 };
  Vector2d initPlayer = { 10, 10 };
  Vector2d initPlayerV = { 0, 0 };
  double initWA = 20;
  double initHA = 55;
  double initWB = 60;
  double initHB = 50;
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
  auto asteroidA = setupBaseEntity(initPosA, initVelA, initWA, initHA, RED);
  auto asteroidB = setupBaseEntity(initPosB, initVelB, initWB, initHB, RED);
  auto base = setupBaseEntity(initPlayer, initPlayerV, initWB, initHB, YELLOW);
  auto ship = setupPlayerEntity(base, keyMap);

  // setup systems
  Bound bound;
  Events events;
  KeyboardEvents<EvUserMovement> keyboardEvents;
  Movement movement;
  RectangleRenderer rectangle(&renderer);
  Thrust thrust;

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
