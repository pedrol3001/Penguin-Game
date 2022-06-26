#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.h"
#include "Music.h"
#include <memory>

class State {
public:
  State();
  virtual ~State();

  virtual void Input() = 0;
  virtual void AddObject(int mouseX, int mouseY) = 0;
  virtual void LoadAssets() = 0;

  bool QuitRequested();
  void Update(float dt);
  void Render();
protected:
  bool quitRequested;
  vector<unique_ptr<GameObject>>objectArray;
};

#endif