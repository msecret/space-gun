
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include <memory>
#include <string>

#include "SDL2/SDL.h"

#include "renderer.h"
#include "units.h"

namespace aronnax {
  using std::string;

class SDLRenderer : public IRenderer
{
  public:
    ~SDLRenderer();
    SDLRenderer(SDL_Window* window);
    void render();
    void beforeRender();
    void afterRender();
    void drawCircle(const Vector2d& pos, const Vector2d& r);
    void drawRectangle(
        const Vector2d& pos,
        const Vector2d& box,
        SDL_Texture* texture,
        float angle);
    void drawPolygon(const Vector2d& pos);
    void drawText(
        const Vector2d& pos,
        string message,
        const Color& color);
    SDL_Texture* createTexture(SDL_Surface& s);

  private:
    // TODO should this be a pointer?
    SDL_Window& screen_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;
};

}

#endif
