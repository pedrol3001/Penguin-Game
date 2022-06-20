#include "game.h"
#include "SDL_exception.h"

#define FLAGS_IMG (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)
#define FLAGS_MIX /*MIX_INIT_MP3 |*/ MIX_INIT_OGG

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height){
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) throw(SDL_Exception());
  if ((IMG_Init(FLAGS_IMG) & FLAGS_IMG) != FLAGS_IMG) throw(SDL_Exception());
  if ((Mix_Init(FLAGS_MIX) & FLAGS_MIX) != FLAGS_MIX) throw(SDL_Exception());
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) throw(SDL_Exception());
  if (TTF_Init() != 0) throw(SDL_Exception());

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr) throw(SDL_Exception());

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == nullptr) throw(SDL_Exception());
}

void Game::Run(){
    while(!GetState().QuitRequested()) {
        GetState().Update(0);
        GetState().Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

Game::~Game(){
  TTF_Quit();
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

Game& Game::GetInstance(){
  if(instance == nullptr){
      instance = new Game(TITLE, WIDTH, HEIGHT);
  }
  return *instance;
}

Game& Game::GetInstance(string title, int width, int height) {
  if(instance == nullptr){
      instance = new Game(title, width, height);
  }
  return *instance;
}

void Game::SetState(State *state){
  this->state = state;
}

State& Game::GetState(){
  return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}