
#ifndef _h_Units
#define _h_Units

namespace aronnax {

struct Vector2d
{
  double x;
  double y;

  Vector2d(const int x=0, const int y=0): x(x), y(y)
  {
  }

  Vector2d operator+(const Vector2d& a) const
  {
    return Vector2d(a.x + x, a.y + y);
  }
};

}

#endif
