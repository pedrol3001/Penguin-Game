#ifndef PENGUIN_STATE_HPP
#define PENGUIN_STATE_HPP

#include "Sprite.h"
#include "State.h"

class PenguinState: public State {
public:
  PenguinState();
  void LoadAssets();
};

#endif