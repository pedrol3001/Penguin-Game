#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <string>
#include <memory>
#include "Rect.h"
#include "Component.h"

using namespace std;

class Component;

class GameObject {
public:
  GameObject(bool skipAutoObjectAddition = false);
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

  void NotifyCollision(GameObject& other);

  Rect box;
  double angleDeg;
private:
  vector<unique_ptr<Component>> components;
  bool started;
  bool isDead;
};

#endif