#include <algorithm>
#include <GameObject.h>
#include <Game.h>

GameObject::GameObject(bool skipAutoObjectAddition) : angleDeg(0), started(false), isDead(false){
  if(skipAutoObjectAddition) return;

  Game::GetInstance().GetCurrentState().AddObject(this);
}

GameObject::GameObject(vector<shared_ptr<GameObject>> *objectArray) : GameObject(true){
  objectArray->emplace_back(this);
}

GameObject::~GameObject(){
  components.clear();
}

void GameObject::Start(){
  for(long unsigned int i = 0; i < components.size(); i++) components[i]->Start();
  started = true;
}

void GameObject::Update(float dt){
  for(long unsigned int i = 0; i < components.size(); i++) components[i]->Update(dt);
}

void GameObject::Render(){
  for(long unsigned int i = 0; i < components.size(); i++) components[i]->Render();
}

bool GameObject::IsDead(){
  return isDead;
}

void GameObject::RequestDelete(){
  isDead = true;
}

void GameObject::AddComponent(Component *cpt){
  components.emplace_back(cpt);
  if(started) cpt->Start();
}

void GameObject::RemoveComponent(Component *cpt){
  erase_if(components, [&cpt](unique_ptr<Component> &obj){ return obj.get() == cpt; });
}

Component *GameObject::GetComponent(string type){
  auto it = find_if(components.begin(), components.end(),[&type](unique_ptr<Component> &obj){ return obj->Is(type);});
  if(it != components.end()) return it->get();
  return nullptr;
}

void GameObject::NotifyCollision(GameObject& other){
  for(long unsigned int i = 0; i < components.size(); i++) components[i]->NotifyCollision(other);
}