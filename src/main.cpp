
#include <iostream>
#include <memory>
#include <stdio.h>

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
#include "c_moveable.h"
#include "c_rectangular.h"

#include "s_bound.h"
#include "s_movement.h"
#include "s_rectangle_renderer.h"
#include "s_sdl_events.h"

using namespace aronnax;
using namespace spacegun;

const int WORLD_W = 640;
const int WORLD_H = 480;

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

Entity* setupEntity(Vector2d initP, Vector2d initV, double w, double h) 
{
  Vector2d bounds = { WORLD_W, WORLD_H };
  Moveable* moveable = new Moveable(initV);
  Rectangular* rectangular = new Rectangular(w, h);
  Boundable* boundable = new Boundable(bounds);

  auto entity = new Entity();
  entity->setPos(initP);
  entity->addComponent(moveable);
  entity->addComponent(rectangular);
  entity->addComponent(boundable);

  return entity;
}

int main()
{
  using namespace std::placeholders;

  // SDL setup
  setupSDL();
  auto window = setupVideo(WORLD_W, WORLD_H);
  atexit(SDL_Quit);

  // aronnax setup
  Clock clock;
  SDLRenderer renderer = SDLRenderer(window);
  Manager manager = Manager(renderer);

  // initial values
  Vector2d initVelA = { 1, 2 };
  Vector2d initVelB = { 3, 2 };
  Vector2d initPosA = { 30, 50 };
  Vector2d initPosB = { 20, 0 };
  double initWA = 20;
  double initHA = 55;
  double initWB = 60;
  double initHB = 50;
  

  // setup asteroids
  auto asteroidA = setupEntity(initPosA, initVelA, initWA, initHA);
  auto asteroidB = setupEntity(initPosB, initVelB, initWB, initHB);

  // setup systems
  Bound bound;
  Events events;
  Movement movement;
  RectangleRenderer rectangle(&renderer);

  // setup to manager
  manager.addEntity(*asteroidA);
  manager.addEntity(*asteroidB);
  manager.addSystem(&bound);
  manager.addSystem(&events);
  manager.addSystem(&movement);
  manager.addSystem(&rectangle);

  // clock manager
  function<void(const uint32_t)> f_update = bind(
      &Manager::update, &manager, _1);
  function<void(const uint32_t)> f_render = bind(
      &Manager::render, &manager, _1);
  clock.onConstantly(f_update);
  clock.onEveryFrame(f_render);
  clock.start();

  return 0;
}
