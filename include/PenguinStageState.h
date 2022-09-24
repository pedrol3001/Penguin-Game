#ifndef PENGUIN_STATE_H
#define PENGUIN_STATE_H

#include <Sprite.h>
#include <StageState.h>

#define MAP_WIDTH 1408
#define MAP_HEIGHT 1280
class PenguinStageState: public StageState {
public:
  PenguinStageState();
  ~PenguinStageState();

private:
  void LoadAssets();
  void UpdateGameData();
};

#endif