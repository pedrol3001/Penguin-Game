#include "State.h"
#include "Camera.h"

State::State() : quitRequested(false) {}

State::~State() {
  objectArray.clear();
}

bool State::QuitRequested() {
  return quitRequested;
}

void State::Update(float dt) {
  Camera::Update(dt);
  Input();
  for(auto& o : objectArray) o->Update(dt);
  for(long unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin()+i);
  }
}

void State::Render() {
  for(auto& o : objectArray) o->Render();
}