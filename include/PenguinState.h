#ifndef PENGUIN_STATE_H
#define PENGUIN_STATE_H

#include "Sprite.h"
#include "State.h"

class PenguinState: public State {
public:
  PenguinState();
  ~PenguinState();

private:
  void LoadAssets();
};

#endif