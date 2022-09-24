#ifndef BULLET_H
#define BULLET_H

#include <Component.h>

class Bullet : public Component {
public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer);

  void NotifyCollision (GameObject& other);
  void Update(float dt);
  void Render();
  bool Is(string type);

  int GetDamage();
  bool IsTargetingPlayer();

private:
  bool targetsPlayer;
  Vec2 speed;
  float distanceLeft;
  int damage;
};

#endif