#include <algorithm>
#include "GameObject.h"

#include <algorithm>

GameObject::GameObject() : isDead(false) {}

GameObject::GameObject(vector<unique_ptr<GameObject>> *objectArray) : GameObject(){
  objectArray->emplace_back(this);
}

GameObject::~GameObject() {
  components.clear();
}

void GameObject::Update(float dt) {
  for(auto& c : components) c->Update(dt);
}

void GameObject::Render() {
  for(auto& c : components) c->Render();
}

bool GameObject::IsDead() {
  return isDead;
}

void GameObject::RequestDelete() {
  isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
  components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
  erase_if(components, [&cpt](unique_ptr<Component> &obj){ return obj.get() == cpt; });
}

Component *GameObject::GetComponent(string type) {
  auto it = find_if(components.begin(), components.end(),[&type](unique_ptr<Component> &obj){ return obj->Is(type);});
  if(it != components.end()) return it->get();
  return nullptr;
}