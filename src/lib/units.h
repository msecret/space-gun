
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <string>

#include <Box2D/Box2D.h>
#include "SDL2/SDL.h"

#ifndef _h_Units
#define _h_Units

using namespace std;

namespace aronnax {

  using Vector2d = b2Vec2;

  /*
  struct Vector2d
  {
    float x;
    float y;

    Vector2d() :
      x(0), y(0)
    { }

    Vector2d(float x, float y): x(x), y(y)
    { }

    // b2d
    void SetZero()
    {
      x = 0.0f;
      y = 0.0f;
    }

    // b2d
    void Set(float x_, float y_) { x = x_; y = y_; }

    // b2d
    Vector2d operator -() const { Vector2d v; v.Set(-x, -y); return v; }


    float operator () (int i) const
    {
      return (&x)[i];
    }

    float& operator () (int i)
    {
      return (&x)[i];
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

    void operator -= (const Vector2d& v)
    {
      x -= v.x; y -= v.y;
    }

    Vector2d& operator*=(const float f)
    {
      x *= f;
      y *= f;

      return *this;
    }

    Vector2d& operator=(const Vector2d& other)
    {
      x = other.x;
      y = other.y;

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

    float Length() const
    {
      return sqrt(x * x + y * y);
    }

    float LengthSquared() const
    {
      return x * x + y * y;
    }


    float Normalize()
    {
      float length = Length();
      if (length < FLT_EPSILON)
      {
        return 0.0f;
      }
      float invLength = 1.0f / length;
      x *= invLength;
      y *= invLength;

      return length;
    }

    bool IsValid() const
    {
      return !!x && !!y;
    }

    Vector2d Skew() const
    {
      return Vector2d(-y, x);
    }
  };
  */

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
  class Ev
  {
    public:
      virtual ~Ev() { };
  };

  const unsigned int EV_KEY = 101;
  enum EvKeyState { STATE_DOWN, STATE_UP };
  class EvKeyboard : public Ev
  {
    public:
      // TODO create constructor for SDL key state.
      EvKeyboard(string key, EvKeyState state) :
        key_(key),
        keyState_(state)
      { }

      EvKeyboard(const SDL_KeyboardEvent& sdlEvent) :
        key_(""),
        keyState_(EvKeyState::STATE_DOWN)
      {
        string keyName = SDL_GetKeyName(sdlEvent.keysym.sym);
        EvKeyState keyState;
        if (sdlEvent.state == SDL_PRESSED) {
          keyState = STATE_UP;
        } else {
          keyState = STATE_DOWN;
        }

        key_ = keyName;
        keyState_ = keyState;
      }

      string getKey()
      {
        return key_;
      }

      void setKey(string key)
      {
        key_ = key;
      }

      EvKeyState getKeyState()
      {
        return keyState_;
      }

      void setKeyState(EvKeyState keyState)
      {

        keyState_ = keyState;
      }

    private:
      string key_;
      EvKeyState keyState_;
  };

  const unsigned int EV_USER_MOVEMENT = 201;
  class EvUserMovement : public Ev
  {
    public:
      EvUserMovement(const Ev& ev) :
        Ev(ev)
      { }

      EvUserMovement(Vector2d dir) :
        direction_(dir)
      { }

      Vector2d getDirection()
      {
        return direction_;
      }

      void setDirection(Vector2d direction)
      {
        direction_ = direction;
      }

    private:
      Vector2d direction_;
  };

  const unsigned int EV_USER_ROTATION = 202;
  class EvUserRotation : public Ev
  {
    public:
      EvUserRotation(const Ev& ev) :
        Ev(ev)
      { }

      EvUserRotation(float dir) :
        direction_(dir)
      { }

      float getDirection()
      {
        return direction_;
      }

      void setDirection(float direction)
      {
        direction_ = direction;
      }

    private:
      float direction_;
  };
}

#endif
