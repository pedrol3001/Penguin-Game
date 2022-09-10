#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include <string>

using namespace std;

class GameObject;

class Component {
public:
  Component(GameObject &associated);
  virtual ~Component();

  virtual void Start();
  virtual void Render() = 0;
  virtual void Update(float dt) = 0;
  virtual bool Is(string type) = 0;

  virtual void NotifyCollision (GameObject& other);

protected:
  GameObject &associated;
};

#endif