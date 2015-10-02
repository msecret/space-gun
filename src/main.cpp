
#include <iostream>
#include <memory>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/manager.h"
#include "lib/sdl_renderer.h"
#include "lib/time.h"

#include "circle.h"
#include "moveable.h"

const int WIDTH = 640;
const int HEIGHT = 480;

// TODO move to a better place
SDL_Window* setupVideo()
{
  return SDL_CreateWindow("Maximized text",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      WIDTH,
                                      HEIGHT,
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
  std::shared_ptr<aronnax::SDLRenderer> renderer = std::make_shared<aronnax::SDLRenderer>(window);

  // Setup manager
  aronnax::Manager manager = aronnax::Manager(renderer);

  // Set up entities
  aronnax::Components componentList;
  spacegun::Moveable* moveable = new spacegun::Moveable();
  spacegun::Circular* circular = new spacegun::Circular();
  componentList.push_back(moveable);
  componentList.push_back(circular);
  aronnax::EntityPtr ball = manager.add(componentList);
  //ball.get()->v.x = 1.5;
  ball.get()->box = { 10.0, 10.0 };
  SDL_Log("main");

  // Set up loop
  aronnax::Clock* clock = new aronnax::Clock();
  std::function<void(const uint32_t)> f_update = std::bind(
      &aronnax::Manager::update, &manager, _1);
  std::function<void()> f_render = std::bind(
      &aronnax::Manager::render, &manager);

  clock->onConstantly(f_update);
  clock->onEveryFrame(f_render);
  clock->start();

  return 0;
}
