#include <PenguinCannon.h>
#include <Sprite.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Camera.h>
#include <Bullet.h>
#include <Game.h>
#include <Collider.h>

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> pbody) : Component(associated), pbody(pbody), angle(0){
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
  associated.AddComponent(new Collider(associated));

	associated.box += pbody.lock()->box.Center() - associated.box.Center();
}

void PenguinCannon::Update(float dt){
  if(!pbody.lock()) return associated.RequestDelete();

  cooldown.Update(dt);

  int mouseX = InputManager::GetInstance().GetMouseX();
  int mouseY = InputManager::GetInstance().GetMouseY();

  Vec2 mousePos = { static_cast<float>(mouseX) + Camera::pos.x, (float) static_cast<float>(mouseY) + Camera::pos.y };

  angle = mousePos.VInclination(pbody.lock()->box.Center());
  associated.box += pbody.lock()->box.Center() - associated.box.Center();
  associated.angleDeg = angle * (180 / M_PI);

  if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) Shoot();
}

void PenguinCannon::Shoot(){
  if(cooldown.Get() <= 0.5) return;

	GameObject* bullet = new GameObject();
	bullet->AddComponent(new Bullet(*bullet, angle, 500, 20, 600, "assets/img/penguinbullet.png", 4, 0.2, false));
	bullet->box += associated.box.Center() - bullet->box.Center();

  cooldown.Restart();
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(string type){
	return type == "PENGUIN_CANNON";
}

