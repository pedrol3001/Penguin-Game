#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

class Bullet : public Component {
public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite);

  void Update(float dt);
  void Render();
  bool Is(string type);

  int getDamage();

private:
  Vec2 speed;
  float distanceLeft;
  int damage;
};


#endif