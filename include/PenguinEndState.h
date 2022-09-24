#ifndef PENGUIN_END_STATE_H
#define PENGUIN_END_STATE_H

#include <State.h>
#include <Music.h>
#include <Timer.h>

class PenguinEndState : public State{
public:
  PenguinEndState();
  ~PenguinEndState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();

private:
  Music backgroundMusic;
};

#endif