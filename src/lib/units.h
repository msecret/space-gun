
#ifndef _h_Units
#define _h_Units

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
    return Vector2d(a.x - x, a.y - y);
  }

  Vector2d operator*(const Vector2d& a) const
  {
    return Vector2d(a.x * x, a.y * y);
  }

  Vector2d& operator+=(const Vector2d& v) 
  { 
    x += v.x;
    y += v.y; 

    return *this; 
  }

  bool operator==(const Vector2d& a) const
  {
    return a.x == x && a.y == y;
  }
};

}

#endif
