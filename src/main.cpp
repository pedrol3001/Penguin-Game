#include "SDL_exception.h"
#include "penguin_state.h"
#include "game.h"

#define TITLE "Penguin"
#define WIDTH 1024
#define HEIGHT 600

int main (int argc, char** argv) {
  try{
    Game::GetInstance(TITLE, WIDTH, HEIGHT).SetState(new PenguinState());
    Game::GetInstance().Run();
  }catch(SDL_Exception err){
    err.Log();
  }
  return 0;
}