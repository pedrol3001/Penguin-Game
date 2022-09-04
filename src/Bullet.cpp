#include "Bullet.h"

#include "Sprite.h"

Bullet::Bullet(
    GameObject &associated,
    float angle,
    float speed,
    int damage,
    float maxDistance,
    string sprite,
    int frameCount,
    float frameTime
  ) : Component(associated), distanceLeft(maxDistance) {

  associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));

  this->speed = Vec2(speed, 0).Rotate(angle);
}

void Bullet::Update(float dt) {
  Vec2 speedVal = speed * dt;
  associated.box += speedVal;
  distanceLeft -= speedVal.Magnitude();
  if(distanceLeft <= 0) associated.RequestDelete();
}

int Bullet::getDamage() {
  return damage;
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
  return type == "BULLET";
}
