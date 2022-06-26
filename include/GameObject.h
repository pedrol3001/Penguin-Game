#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include <string>
#include <memory>
#include <vector>
#include "Rect.h"
#include "Component.h"

using namespace std;

class Component;

class GameObject {
public:
  GameObject();
  GameObject(vector<unique_ptr<GameObject>> *objectArray);
  ~GameObject();

  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(string type);

  Rect box;
private:
  vector<unique_ptr<Component>> components;
  bool isDead;
};

#endif