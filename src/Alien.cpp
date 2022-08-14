#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed({0, 0}), hp(50) {
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
  minionArray.resize(nMinions);
}

Alien::~Alien() {
  for (auto &minion : minionArray) minion.lock()->RequestDelete();
  minionArray.clear();
}

void Alien::Start() {
  unsigned int minionSize = minionArray.size();
  for(unsigned i = 0; i < minionSize; i++){
    weak_ptr<GameObject> alien = Game::GetInstance().GetState().GetObjectPtr(&associated);

    GameObject *minion = new GameObject();
    minion->AddComponent(new Minion(*minion, alien,  (static_cast<float>(i) / minionSize) * 2 * M_PI));
    minionArray[i] = Game::GetInstance().GetState().AddObject(minion);
  }
}

void Alien::Update(float dt) {
  associated.angleDeg -= 5;

  InputManager inputManager = InputManager::GetInstance();
  Vec2 mouse = inputManager.GetMouse();

  if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
    taskQueue.push(*new Action(Action::SHOOT, mouse.x , mouse.y));
  }
  if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){
    taskQueue.swap(*new queue<Action>());
    taskQueue.push(*new Action(Action::MOVE, mouse.x, mouse.y));
  }

  if (taskQueue.empty()) return;

  Action action = taskQueue.front();

  if(action.type == Action::MOVE){
    Vec2 speed = { 500 * dt, 0 };
    Vec2 movement = action.pos - Vec2(associated.box.x + (associated.box.w / 2), associated.box.y + (associated.box.h / 2));
    Vec2 direction = speed.Rotate(movement.XInclination());

    if(movement.Magnitude() >= direction.Magnitude()){
      associated.box +=  direction;
    } else {
      taskQueue.pop();
    }
  }
  if(action.type == Action::SHOOT){
    Minion* minion = dynamic_cast<Minion*>(minionArray[0].lock()->GetComponent("MINION"));
    minion->Shoot(mouse);

    taskQueue.pop();
  }
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type){
  pos.x = x;
  pos.y = y;
}

void Alien::Render() {}

bool Alien::Is(string type) {
  return type == "ALIEN";
}
