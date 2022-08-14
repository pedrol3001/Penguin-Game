#include "State.h"
#include "Camera.h"
#include "InputManager.h"

State::State() :  started(false), quitRequested(false){}

State::~State() {
  objectArray.clear();
}

bool State::QuitRequested() {
  return quitRequested;
}

void State::Update(float dt) {
  Camera::Update(dt);
  quitRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested();

  for(long unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i].get()->Update(dt);
    if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin()+i);
  }
}

void State::Render() {
  for(auto& o : objectArray) o->Render();
}

weak_ptr<GameObject> State::AddObject(GameObject *go){
  shared_ptr<GameObject> object(go);

  objectArray.push_back(object);
  if(started) object->Start();
  return weak_ptr<GameObject>(object);
}

weak_ptr< GameObject > State::GetObjectPtr(GameObject *go){
  for (auto &o : objectArray) if(o.get() == go) return weak_ptr<GameObject>(o);
  return weak_ptr<GameObject>();
}

void State::Start(){
  for(auto& o : objectArray) o->Start();
  started = true;
}