
#include <cstdint>
#include <string>

#include "SDL2/SDL.h"

#ifndef _h_Units
#define _h_Units

using namespace std;

namespace aronnax {

  struct Vector2d
  {
    double x;
    double y;

    Vector2d(const double x=0, const double y=0): x(x), y(y)
    {
    }

    Vector2d operator+(const Vector2d& a) const
    {
      return Vector2d(a.x + x, a.y + y);
    }

    Vector2d operator-(const Vector2d& a) const
    {
      return Vector2d(x - a.x, y - a.y);
    }

    Vector2d operator*(const Vector2d& a) const
    {
      return Vector2d(a.x * x, a.y * y);
    }

    Vector2d operator/(const Vector2d& a) const
    {
      return Vector2d(x / a.x, y / a.y);
    }

    Vector2d& operator+=(const Vector2d& v)
    {
      x += v.x;
      y += v.y;

      return *this;
    }

    Vector2d& operator*=(const double f)
    {
      x *= f;
      y *= f;

      return *this;
    }

    bool operator==(const Vector2d& a) const
    {
      return a.x == x && a.y == y;
    }

    bool operator!=(const Vector2d& a) const
    {
      return x != a.x && y != a.y;
    }
  };

  struct Color
  {
    uint8_t r, g, b, a;

    Color(const uint8_t red=0,
          const uint8_t green=0,
          const uint8_t blue=0,
          const uint8_t alpha=0) :
      r(red),
      g(green),
      b(blue),
      a(alpha)
    { }

    bool operator==(const Color& c) const
    {
      return r == c.r && g == c.g && b == c.b && a == c.a;
    }

    bool operator!=(const Color& c) const
    {
      return r != c.r || g != c.g || b != c.b || a != c.a;
    }
  };

  const unsigned int EV = 100;
  struct Ev
  {
    bool active;

    Ev() :
      active(true)
    { }
  };

  const unsigned int EV_KEY = 101;
  enum EvKeyState { STATE_DOWN, STATE_UP };
  struct EvKeyboard : Ev
  {
    string key;
    EvKeyState keyState;

    // TODO create constructor for SDL key state.
    EvKeyboard(string key, EvKeyState state) :
      key(key),
      keyState(state)
    { }

    EvKeyboard(const SDL_KeyboardEvent& sdlEvent)
    {
      string keyName = SDL_GetKeyName(sdlEvent.keysym.sym);
      EvKeyState keyState;
      if (sdlEvent.state == SDL_PRESSED) {
        keyState = STATE_UP;
      } else {
        keyState = STATE_DOWN;
      }

      key = keyName;
      keyState = keyState;
    }
  };

  const unsigned int EV_USER_MOVEMENT = 201;
  struct EvUserMovement : Ev
  {
    Vector2d direction;

    EvUserMovement(Vector2d dir) :
      direction(dir)
    { }
  };
}

#endif
