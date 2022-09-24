#include <PenguinBody.h>
#include <Sprite.h>
#include <Camera.h>
#include <PenguinCannon.h>
#include <InputManager.h>
#include <Game.h>
#include <Sound.h>
#include <Collider.h>
#include <Bullet.h>
#include <PenguinStageState.h>

#define PENGUIN_ACCELERATION 6
#define PENGUIN_SPEED_LIMIT 300
#define PENGUIN_ANGULAR_VELOCITY M_PI / 12

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated), linearSpeed(0), angle(0), hp(50){
	player = this;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
  associated.AddComponent(new Collider(associated));
}

PenguinBody::~PenguinBody(){
	player = nullptr;
}

void PenguinBody::Start(){
  weak_ptr<GameObject> pbody = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

  GameObject *cannonGo = new GameObject();
	cannonGo->AddComponent(new PenguinCannon(*cannonGo, pbody));

	pcannon = Game::GetInstance().GetCurrentState().GetObjectPtr(cannonGo);
}

void PenguinBody::Update(float dt){
	InputManager inputManager = InputManager::GetInstance();

	if (inputManager.IsKeyDown('w')){
		linearSpeed = min(linearSpeed + 20, static_cast<float>(400));
	}
  else if (inputManager.IsKeyDown('s')){
		linearSpeed = max(linearSpeed - 20, static_cast<float>(-400));
	}
	else {
		if (linearSpeed < 0){
      linearSpeed = min(linearSpeed + 20, static_cast<float>(0));
		}
		if (linearSpeed > 0){
			linearSpeed = max(linearSpeed - 20, static_cast<float>(0));
		}
	}

	if (inputManager.IsKeyDown('a')){
		angle += M_PI / 10;
	}
  if (inputManager.IsKeyDown('d')){
		angle -= M_PI / 10;
	}

	Rect dest = associated.box + Vec2(linearSpeed, 0).Rotate(angle) * dt;
	if(dest.x <= 0) dest.x = 0;
	if(dest.y <= 0) dest.y = 0;
	if(dest.x >= MAP_WIDTH - associated.box.w) dest.x = MAP_WIDTH - associated.box.w;
	if(dest.y >= MAP_HEIGHT- associated.box.h) dest.y = MAP_HEIGHT- associated.box.h;
	associated.box = dest;

	pcannon.lock()->box += Vec2(linearSpeed, 0).Rotate(angle) * dt;
	associated.angleDeg = angle * 180 / M_PI;

	if (hp <= 0){
		GameObject* death = new GameObject();

    death->box = associated.box;

		death->AddComponent(new Sprite(*death, "assets/img/penguindeath.png", 5, 0.3, 1.0));

		Sound* sound = new Sound(*death, "assets/audio/boom.wav");
		death->AddComponent(sound);
		sound->Play();

		Camera::Unfollow();

		associated.RequestDelete();
		pcannon.lock()->RequestDelete();
	}
}

Vec2 PenguinBody::Center(){
  return associated.box.Center();
}

void PenguinBody::NotifyCollision(GameObject& other){
  Bullet* bullet = dynamic_cast<Bullet*>(other.GetComponent("BULLET"));

	if (bullet == nullptr) return;

  if (!bullet->IsTargetingPlayer()) return;

  hp -= bullet->GetDamage();
}

void PenguinBody::Render(){}

bool PenguinBody::Is(string type){
	return type == "PENGUIN_BODY";
}