#define TITLE "Penguin"
#define WIDTH 1024
#define HEIGHT 600

#include "SDL_exception.h"
#include "penguin_state.h"
#include "game.h"

#include <iostream>
using namespace std;

int main (int argc, char** argv) {
  try{
    Game::GetInstance(TITLE, WIDTH, HEIGHT).SetState(new PenguinState());
    Game::GetInstance().Run();
  }catch(std::exception &err){
    cout << err.what() << endl;
  }
  return 0;
}