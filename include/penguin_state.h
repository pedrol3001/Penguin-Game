#ifndef PENGUIN_STATE_HPP
#define PENGUIN_STATE_HPP

#include "sprite.h"
#include "state.h"

class PenguinState: public State {
public:
  PenguinState();
  void LoadAssets();
};

#endif