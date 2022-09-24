#include <Camera.h>
#include <Game.h>
#include <InputManager.h>

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
  if (focus != nullptr){
    float x = focus->box.x - Game::GetInstance().GetWidth() / 2;
    float y = focus->box.y - Game::GetInstance().GetHeight() / 2;
    pos = Vec2(x, y);
  }
  else{
    Vec2 speed(0, 0);

    InputManager inputManager = InputManager::GetInstance();

    bool up_pressed = inputManager.IsKeyDown(UP_ARROW_KEY);
    bool down_pressed = inputManager.IsKeyDown(DOWN_ARROW_KEY);
    bool right_pressed = inputManager.IsKeyDown(RIGHT_ARROW_KEY);
    bool left_pressed = inputManager.IsKeyDown(LEFT_ARROW_KEY);

    if(up_pressed){
     speed += Vec2(0, -CAMERA_SPEED * dt);
    }
    if(down_pressed){
      speed += Vec2(0, CAMERA_SPEED * dt);
    }
    if(right_pressed){
      speed += Vec2(CAMERA_SPEED * dt, 0);
    }
    if(left_pressed){
      speed += Vec2(-CAMERA_SPEED * dt, 0);
    }

    pos += speed;
  }
}