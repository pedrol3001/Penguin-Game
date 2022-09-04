#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Minion.h"

Minion::Minion(
  GameObject &associated,
  weak_ptr<GameObject> alienCenter,
  float arcOffsetDeg
) : Component(associated), alienCenter(*(alienCenter.lock())), arc(arcOffsetDeg) {
  Sprite *sprite = new Sprite(associated, "assets/img/minion.png");
  associated.AddComponent(sprite);
}

void Minion::Update(float dt) {
  arc += (M_PI / 64);
  Vec2 pos = Vec2(200, 0).Rotate(arc);

  associated.box += (pos - associated.box.Center() + alienCenter.box.Center());

  associated.angleDeg = pos.XInclination() * 180 / M_PI;
}

void Minion::Shoot(Vec2 target) {
  float angle = (target - associated.box.Center()).XInclination();

  GameObject *bullet = new GameObject();
  bullet->AddComponent(new Bullet(*bullet, angle, 300, 20, 700, "assets/img/minionbullet2.png", 3, 0.2));

  bullet->box.x = associated.box.Center().x - bullet->box.w/2;
  bullet->box.y = associated.box.Center().y - bullet->box.h/2;

  bullet->angleDeg = angle * 180 / M_PI;

  Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::Render() {}

bool Minion::Is(string type) {
  return type == "MINION";
}