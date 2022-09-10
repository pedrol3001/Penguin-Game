#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
  Rect();
  Rect(float x, float y, float w, float h);

  Rect operator+(const Vec2& vec);
  Rect operator+=(const Vec2& vec);
  Rect operator-(const Vec2& vec);
  Rect operator-=(const Vec2& vec);
  Vec2 Center();

  float CenterDist(Rect r);
  bool Contains(Vec2 v);

  float x;
  float y;
  float w;
  float h;
};

#endif