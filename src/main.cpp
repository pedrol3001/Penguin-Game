#define TITLE "Pedro Luis Chaves Rocha - 180054635"
#define WIDTH 1024
#define HEIGHT 600

#include <SDL_exception.h>
#include <PenguinTitleState.h>
#include <Game.h>

#include <iostream>
using namespace std;

int main (int argc, char** argv){
  srand(time(NULL));

  try{
    Game& game = Game::GetInstance(TITLE, WIDTH, HEIGHT);
    game.Push(new PenguinTitleState());
    game.Run();
  }catch(SDL_Exception& e){
    cout << e.what() << endl;
  }
  return 0;
}