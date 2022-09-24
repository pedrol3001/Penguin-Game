#ifndef NULL_GAME_OBJECT_H
#define NULL_GAME_OBJECT_H

#include <GameObject.h>

using namespace std;

class NullGameObject : public GameObject{
public:
  NullGameObject() : GameObject(true){}
};

#endif