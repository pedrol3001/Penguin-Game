#include <Sprite.h>
#include <Bullet.h>
#include <Game.h>
#include <Minion.h>
#include <Collider.h>

Minion::Minion(
  GameObject &associated,
  weak_ptr<GameObject> alienCenter,
  float arcOffsetDeg
) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
  associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
  associated.AddComponent(new Collider(associated));
}

void Minion::Update(float dt){
  if(!alienCenter.lock()) return associated.RequestDelete();

  arc += (M_PI / 64);
  Vec2 pos = Vec2(140, 0).Rotate(arc);

  associated.box += alienCenter.lock()->box.Center() + (pos - associated.box.Center());
  associated.angleDeg = pos.XInclination() * 180 / M_PI;
}

void Minion::Shoot(Vec2 target){
  float angle = (target - associated.box.Center()).XInclination();

  GameObject *bullet = new GameObject();
  bullet->AddComponent(new Bullet(*bullet, angle, 750, 20, 700, "assets/img/minionbullet2.png", 3, 0.2, true));

  bullet->box += associated.box.Center() - bullet->box.Center();
}

void Minion::Render(){}

bool Minion::Is(string type){
  return type == "MINION";
}