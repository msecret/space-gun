
#ifndef _h_Positioning
#define _h_Positioning


struct Vector2d
{
  double x;
  double y;

  Vector2d(int x=0, int y=0): x(x), y(y)
  {
  }

  Vector2d operator+(const Vector2d& a) const
  {
    return Vector2d(a.x + x, a.y + y);
  }
};

#endif
