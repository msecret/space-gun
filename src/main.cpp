
#include <iostream>
#include <memory>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/manager.h"
#include "lib/sdl_renderer.h"
#include "lib/time.h"

#include "bounded.h"
#include "circle.h"
#include "keyboardable.h"
#include "moveable.h"
#include "world.h"

// TODO move to a better place
SDL_Window* setupVideo()
{
  return SDL_CreateWindow("Maximized text",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      WORLD_W,
                                      WORLD_H,
                                      SDL_WINDOW_RESIZABLE);
}

int main()
{
  using namespace std::placeholders;

  // TODO move elsewhere
  // Setup SDL
  int retval = SDL_Init(SDL_INIT_EVERYTHING);
  if (retval)
  {
      printf("SDL_Init: Couldn't start SDL\n");
      printf("%s\n", SDL_GetError());
  }

  // Setup graphic
  SDL_Window* window = setupVideo();
  std::shared_ptr<aronnax::SDLRenderer> renderer = std::make_shared<
    aronnax::SDLRenderer>(window);

  atexit(SDL_Quit);

  // Setup manager
  aronnax::Manager manager = aronnax::Manager(renderer);

  // Set up entities
  aronnax::Components componentList;
  spacegun::Moveable* moveable = new spacegun::Moveable();
  spacegun::Circular* circular = new spacegun::Circular();
  spacegun::Keyboardable* keyboardable = new spacegun::Keyboardable();
  spacegun::Bounded* bounded = new spacegun::Bounded();

  componentList.push_back(moveable);
  componentList.push_back(circular);
  componentList.push_back(bounded);

  aronnax::IEntityPtr asteroidA = manager.add(componentList);
  asteroidA.get()->v.x = 0.55;
  asteroidA.get()->v.y = 0.35;
  asteroidA.get()->box = { 45.0, 55.0 };
  aronnax::IEntityPtr asteroidB = manager.add(componentList);
  asteroidB.get()->v.x = 0.70;
  asteroidB.get()->v.y = 0.85;
  asteroidB.get()->box = { 45.0, 40.0 };
  aronnax::IEntityPtr asteroidC = manager.add(componentList);
  asteroidC.get()->v.x = 0.40;
  asteroidC.get()->v.y = 0.15;
  asteroidC.get()->box = { 30.0, 27.0 };

  componentList.push_back(keyboardable);
  aronnax::IEntityPtr ball = manager.add(componentList);
  keyboardable->init(*ball.get());
  ball.get()->v.x = 1.5;
  ball.get()->box = { 20.0, 20.0 };
  ball.get()->pos = { 25.0, 30.0 };
  SDL_Log("main");

  // Set up loop
  aronnax::Clock* clock = new aronnax::Clock();
  std::function<void(const uint32_t)> f_update = std::bind(
      &aronnax::Manager::update, &manager, _1);
  std::function<void(const uint32_t)> f_event = std::bind(
      &aronnax::Manager::event, &manager, _1);
  std::function<void()> f_render = std::bind(
      &aronnax::Manager::render, &manager);

  clock->onConstantly(f_update);
  clock->onConstantly(f_event);
  clock->onEveryFrame(f_render);
  clock->start();

  return 0;
}
