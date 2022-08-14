#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include <string>
#include <memory>
#include "Rect.h"
#include "Component.h"

using namespace std;

class Component;

class GameObject {
public:
  GameObject();
  GameObject(vector<shared_ptr<GameObject>> *objectArray);
  ~GameObject();

  void Start();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(string type);

  Rect box;
  double angleDeg;
private:
  vector<unique_ptr<Component>> components;
  bool started;
  bool isDead;
};

#endif