
#ifndef _h_SDLRenderer
#define _h_SDLRenderer

#include <memory>
#include <string>

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include "renderer.h"
#include "units.h"

namespace aronnax {
  using std::string;

class SDLRenderer : public IRenderer
{
  public:
    virtual ~SDLRenderer();
    SDLRenderer() {};
    SDLRenderer(SDL_Window* window);
    virtual void render();
    virtual void beforeRender();
    virtual void afterRender();
    void drawCircle(const Vector2d& pos, const Vector2d& r);
    virtual void drawRectangle(
        const Vector2d& pos,
        const Vector2d& box,
        SDL_Texture* texture,
        float angle);
    void drawPolygon(const Vector2d& pos);
    void drawText(
        const Vector2d& pos,
        string message,
        const Color& color);
    virtual SDL_Texture* createTexture(SDL_Surface& s);
    virtual SDL_Surface* loadImg(const string& filePath);

  private:
    // TODO should this be a pointer?
    SDL_Window* screen_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;
    SDL_Texture* bg_;
};

}

#endif
