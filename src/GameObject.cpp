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
  components.erase(std::remove(components.begin(), components.end(), *new unique_ptr<Component>(cpt)), components.end());
}

Component *GameObject::GetComponent(string type) {
  for(auto& c : components) if (c->Is(type)) return c.get();
  return nullptr;
}