#include "sprite.h"
#include "music.h"
#include "state.h"
#include "game.h"

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