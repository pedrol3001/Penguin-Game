#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed = *new Vec2();
GameObject *Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus){
  focus = newFocus;
}

void Camera::Unfollow(){
  focus = nullptr;
}

void Camera::Update(float dt){
  if(focus != nullptr){
      pos = {focus->box.x - Game::GetInstance().GetWidth()/2, focus->box.y - Game::GetInstance().GetHeight()/2};
  } else {
    InputManager inputManager = InputManager::GetInstance();

    speed = {0, 0};
    Vec2 dir = {CAMERA_SPEED * dt, 0};

    bool up_pressed = inputManager.IsKeyDown(UP_ARROW_KEY);
    bool down_pressed = inputManager.IsKeyDown(DOWN_ARROW_KEY);
    bool right_pressed = inputManager.IsKeyDown(RIGHT_ARROW_KEY);
    bool left_pressed = inputManager.IsKeyDown(LEFT_ARROW_KEY);

    if(right_pressed && down_pressed){
      speed = dir.Rotate(M_PI / 4);
    } else if(left_pressed && down_pressed){
      speed = dir.Rotate(M_PI * 3 / 4);
    } else if(left_pressed && up_pressed){
      speed = dir.Rotate(M_PI * -3 / 4);
    } else if(right_pressed && up_pressed){
      speed = dir.Rotate(M_PI / -4);
    }else if (right_pressed) {
      speed = dir;
    } else if (down_pressed) {
      speed = dir.Rotate(M_PI / 2);
    } else if (left_pressed) {
      speed = dir.Rotate(M_PI);
    } else if (up_pressed) {
      speed = dir.Rotate(M_PI / -2);
    }

    pos += speed;
  }
}