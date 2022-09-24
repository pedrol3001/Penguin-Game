#include <Vec2.h>

Vec2::Vec2() : x(0), y(0){}

Vec2::Vec2(float x, float y) : x(x), y(y){}

Vec2 Vec2::operator+(const Vec2& vec)  {
  return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator+=(const Vec2 &vec){
  return *this = *this + vec;
}

Vec2 Vec2::operator-(const Vec2& vec)  {
  return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator-=(const Vec2& vec)  {
  return *this = *this - vec;
}

Vec2 Vec2::operator*(const float& esc)  {
  return Vec2(x * esc, y * esc);
}

float Vec2::Dot(const Vec2& vec){
  return x * vec.x + y * vec.y;
}

float Vec2::Magnitude(){
  return sqrtf((x * x) + (y * y));
}

Vec2 Vec2::Normalized(){
  return Vec2(x / Magnitude(), y / Magnitude());
}

float Vec2::Dist(Vec2 vec){
  return (*this - vec).Magnitude();
}

float Vec2::XInclination(){
  return atan2(y, x);
}

float Vec2::VInclination(Vec2 vec){
  return (*this - vec).XInclination();
}

Vec2 Vec2::Rotate(float angle){
  float xl = (cos(angle)* x) - (sin(angle)* y);
  float yl = (cos(angle)* y) + (sin(angle)* x);
  return Vec2(xl, yl);
}