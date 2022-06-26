#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0)  {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect Rect::operator+(const Vec2& vec)  {
  return Rect(x + vec.x, y + vec.y, w, h);
}

Rect Rect::operator-(const Vec2& vec)  {
  return Rect(x - vec.x, y - vec.y, w, h);
}

Vec2 Rect::Center() {
  return Vec2(x + (w / 2), y + (h / 2));
}

float Rect::CenterDist(Rect r) {
  Vec2 otherCenter = r.Center();
  return this->Center().Dist(otherCenter);
}

bool Rect::Contains(Vec2 vec) {
  return (vec.x >= x && vec.x <= x + w) && (vec.y >= y && vec.y <= y + h);
}