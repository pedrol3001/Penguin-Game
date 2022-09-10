#include "State.h"
#include "Camera.h"
#include "InputManager.h"
#include "Collider.h"

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

  for (long unsigned int i = 0; i < objectArray.size(); i++) {
    Collider* A = dynamic_cast<Collider*>(objectArray[i]->GetComponent("COLLIDER"));
		if (A == nullptr) continue;

    for (long unsigned int j = i + 1; j < objectArray.size(); j++ ) {
      Collider* B = dynamic_cast<Collider*>(objectArray[j]->GetComponent("COLLIDER"));
      if (B == nullptr) continue;

      if (A->IsColliding(B)) {
        objectArray[i]->NotifyCollision(*objectArray[j].get());
        objectArray[j]->NotifyCollision(*objectArray[i].get());
      }
    }
	}
}

void State::Render() {
  for(long unsigned int i = 0; i < objectArray.size(); i++) objectArray[i]->Render();
}

weak_ptr<GameObject> State::AddObject(GameObject *go){
  shared_ptr<GameObject> object(go);

  objectArray.push_back(object);
  if(started) object->Start();
  return weak_ptr<GameObject>(object);
}

weak_ptr< GameObject > State::GetObjectPtr(GameObject *go){
  for(long unsigned int i = 0; i < objectArray.size(); i++) if(objectArray[i].get() == go) return weak_ptr<GameObject>(objectArray[i]);
  return weak_ptr<GameObject>();
}

void State::Start(){
  for(long unsigned int i = 0; i < objectArray.size(); i++) objectArray[i]->Start();
  started = true;
}