#ifndef COMPONENT_HPP
#define COMPONENT_HPP

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

protected:
  GameObject &associated;
};

#endif