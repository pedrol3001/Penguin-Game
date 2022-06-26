#include "Penguin_state.h"

PenguinState::PenguinState() : State() {
  LoadAssets();
  music.Play();
}

void PenguinState::LoadAssets(){
  music.Open("assets/audio/stageState.ogg");
  bg.Open("assets/img/ocean.jpg");
}