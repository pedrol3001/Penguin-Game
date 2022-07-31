#include "Face.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"

Face::Face(GameObject &associated) : Component(associated), hitPoints(30) {}

void Face::Damage(int damage){
  hitPoints -= damage;
  if (hitPoints > 0) return;

  Sprite* sprite = dynamic_cast<Sprite*>(associated.GetComponent("SPRITE"));
  Sound* sound = dynamic_cast<Sound*>(associated.GetComponent("SOUND"));
  if (sprite == nullptr || sound == nullptr) return associated.RequestDelete();

  sound->Play();
  associated.RemoveComponent(sprite);
}

void Face::Update(float dt){
  InputManager inputManager = InputManager::GetInstance();

  bool mouseOver = associated.box.Contains({inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y});

  if(inputManager.MousePress(LEFT_MOUSE_BUTTON) && mouseOver){
    Damage(rand() % 10 + 10);
  }
}

void Face::Render(){}

bool Face::Is(string type){
  return type == "FACE";
}