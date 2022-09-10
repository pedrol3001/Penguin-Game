#ifndef VEC2_H
#define VEC2_H

#include <math.h>

class Vec2 {
public:
  Vec2();
  Vec2(float x, float y);

  Vec2 operator+(const Vec2& vec);
  Vec2 operator+=(const Vec2 &vec);
  Vec2 operator-(const Vec2& vec);
  Vec2 operator-=(const Vec2& vec);
  Vec2 operator*(const float& esc);
  float Dot(const Vec2& vec);

  Vec2 Normalized();
  float Magnitude();
  float Dist(Vec2 v);

  float XInclination();
  float VInclination(Vec2 v);

  Vec2 Rotate(float angle);

  float x;
  float y;
};

#endif