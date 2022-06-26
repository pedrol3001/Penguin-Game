#include "Sprite.h"
#include "Music.h"
#include "State.h"
#include "Game.h"

State::State() : quitRequested(false) {}

bool State::QuitRequested() {
  return quitRequested;
}

void State::Update(float dt) {
  quitRequested = SDL_QuitRequested();
}

void State::Render() {
  bg.Render(0, 0);
}