#define TITLE "Pedro Luis Chaves Rocha - 180054635"
#define WIDTH 1024
#define HEIGHT 600

#include "SDL_exception.h"
#include "PenguinState.h"
#include "Game.h"

#include <iostream>
using namespace std;

int main (int argc, char** argv) {
  try{
    Game::GetInstance(TITLE, WIDTH, HEIGHT).SetState(new PenguinState());
    Game::GetInstance().Run();
  }catch(SDL_Exception& e){
    cout << e.what() << endl;
  }
  return 0;
}