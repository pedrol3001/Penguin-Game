#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#define DEFAULT_TITLE "Default"
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 600

#include "SDL_include.h"

#include <string>
#include "asset.h"
#include "state.h"

using namespace std;

class Game {
protected:
  Game(string title, int width, int height);
  ~Game();
  static Game* instance;

public:
  static Game& GetInstance();
  static Game& GetInstance(string title, int width, int height);

  Game(Game &other) = delete;
  void operator=(const Game &) = delete;

  void SetState(State *state);
  State& GetState();

  SDL_Renderer* GetRenderer();
  void Run();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  State* state;
};

#endif