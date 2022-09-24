#include <State.h>
#include <Collider.h>

State::State() : popRequested(false), quitRequested(false), started(false){}

State::~State(){
  objectArray.clear();
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

void State::StartArray(){
  for(long unsigned int i = 0; i < objectArray.size(); i++) objectArray[i].get()->Start();
  started = true;
}

void State::RenderArray(){
  for(long unsigned int i = 0; i < objectArray.size(); i++) objectArray[i].get()->Render();
}

void State::UpdateArray(float dt){
  for(long unsigned int i = 0; i < objectArray.size(); i++){
    objectArray[i].get()->Update(dt);
    if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin()+i);
  }
}

void State::UpdateGameData(){}

bool State::PopRequested(){
  return popRequested;
}

bool State::QuitRequested(){
  return quitRequested;
}
