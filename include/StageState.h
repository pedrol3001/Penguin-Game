#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <Sprite.h>
#include <Music.h>
#include <State.h>
#include <memory>

class StageState : public State {
public:
  StageState();
  virtual ~StageState();

  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
protected:
  virtual void LoadAssets() = 0;
};

#endif