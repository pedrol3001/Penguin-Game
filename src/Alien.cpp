#include <Alien.h>

#include <Sprite.h>
#include <Camera.h>
#include <Minion.h>
#include <Sprite.h>
#include <Game.h>
#include <Collider.h>
#include <Sound.h>
#include <Bullet.h>
#include <PenguinBody.h>

#include <cstdlib>

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed({0, 0}), hp(50), state(RESTING){
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
  associated.AddComponent(new Collider(associated));

  timeOffset = (rand() % 500) / 100;
  minionArray.resize(nMinions);
  alienCount++;
}

Alien::~Alien(){
  for (auto &minion : minionArray) minion.lock()->RequestDelete();
  minionArray.clear();
  alienCount--;
}

void Alien::Start(){
  unsigned int minionSize = minionArray.size();
  for(unsigned i = 0; i < minionSize; i++){
    weak_ptr<GameObject> alien = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

    GameObject *minion = new GameObject();
    minion->AddComponent(new Minion(*minion, alien,  (static_cast<float>(i) / minionSize) * 2 * M_PI));
    minionArray[i] = Game::GetInstance().GetCurrentState().GetObjectPtr(minion);
  }
}

void Alien::Update(float dt){
  associated.angleDeg -= 5;
  restTimer.Update(dt);

  if(PenguinBody::player == nullptr) return;

  Vec2 playerCenter = PenguinBody::player->Center();

  if(state == RESTING && restTimer.Get() >= timeOffset){
    timeOffset = (rand() % 500) / 100;
    destination = playerCenter;
    state = MOVING;
  }

  if(state == MOVING){
    Vec2 dest = destination - associated.box.Center();
    Vec2 direction = Vec2(500 * dt, 0).Rotate(dest.XInclination());

    if(dest.Magnitude() >= direction.Magnitude()){
      associated.box += direction;
    } else {
      float minDistance = FLT_MAX;
      shared_ptr<GameObject> minion;

      for(auto& m : minionArray){
        shared_ptr<GameObject> minionRef = m.lock();

        float dist = minionRef->box.Center().Dist(playerCenter);
        if (dist >= minDistance) continue;

        minDistance = dist;
        minion = minionRef;
      }
      dynamic_cast<Minion*>(minion->GetComponent("MINION"))->Shoot(playerCenter);

      state = RESTING;
      restTimer.Restart();
    }
  }

  if (hp <= 0){
		GameObject* explosion = new GameObject();

    explosion->box = associated.box;
		explosion->AddComponent(new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.3, 1.0));

		Sound* sound = new Sound(*explosion, "assets/audio/boom.wav");
		explosion->AddComponent(sound);

		sound->Play();

		associated.RequestDelete();
	}
}

void Alien::NotifyCollision(GameObject& other){
  Bullet* bullet = dynamic_cast<Bullet*>(other.GetComponent("BULLET"));

	if (bullet == nullptr) return;

  if (bullet->IsTargetingPlayer()) return;

  hp -= bullet->GetDamage();
}

void Alien::Render(){}

bool Alien::Is(string type){
  return type == "ALIEN";
}
