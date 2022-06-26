#ifndef PENGUIN_STATE_HPP
#define PENGUIN_STATE_HPP

#include "Sprite.h"
#include "State.h"

class PenguinState: public State {
public:
  PenguinState();
  ~PenguinState();

  void LoadAssets();
private:
  void AddObject(int mouseX, int mouseY);
  void Input();
};

#endif