#ifndef PENGUIN_TITLE_STATE_H
#define PENGUIN_TITLE_STATE_H

#include <State.h>
#include <Timer.h>
#include <GameObject.h>

class PenguinTitleState : public State {
public:
  PenguinTitleState();
  ~PenguinTitleState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();

private:
  GameObject *blinkingText;
  Timer blinkingTextTimer;
};

#endif