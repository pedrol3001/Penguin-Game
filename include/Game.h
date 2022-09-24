#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#define DEFAULT_TITLE "Default"
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 600

#include <SDL_include.h>

#include <string>
#include <stack>
#include <Asset.h>
#include <State.h>

using namespace std;

class Game {
private:
  Game(string title, int width, int height);
  ~Game();
  static Game* instance;

public:
  static Game& GetInstance();
  static Game& GetInstance(string title, int width, int height);

  Game(Game &other) = delete;
  void operator=(const Game &) = delete;

  SDL_Renderer* GetRenderer();
  void Run();

  void CalculateDeltaTime();
  float GetDeltaTime();

  int GetWidth();
  int GetHeight();

  void Push(State* state);
  State& GetCurrentState();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  State* storedState;
  stack<unique_ptr<State>> stateStack;

  int width, height;

  int frameStart;
  float dt;
};

#endif