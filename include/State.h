#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.h"
#include "Music.h"

class State {
public:
  State();

  virtual void LoadAssets() = 0;

  bool QuitRequested();
  void Update(float dt);
  void Render();
protected:
  Sprite bg;
  Music music;
  bool quitRequested;
};

#endif