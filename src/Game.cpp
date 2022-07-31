#include "Game.h"
#include "Resources.h"
#include "SDL_exception.h"
#include "InputManager.h"

#define FLAGS_IMG (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)
#define FLAGS_MIX /*MIX_INIT_MP3 |*/ MIX_INIT_OGG

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height){
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) throw(SDL_Exception("SDL_Init Failed"));
  if ((IMG_Init(FLAGS_IMG) & FLAGS_IMG) != FLAGS_IMG) throw(SDL_Exception("SDL IMG_Init Failed"));
  if ((Mix_Init(FLAGS_MIX) & FLAGS_MIX) != FLAGS_MIX) throw(SDL_Exception("SDL Mix_Init Failed"));
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) throw(SDL_Exception("SDL Mix_OpenAudio Failed"));
  if (TTF_Init() != 0) throw(SDL_Exception("SDL TTF_Init Failed"));

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr) throw(SDL_Exception("Failed to create window"));

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) throw(SDL_Exception("Failed to render window"));

  this->width = width;
  this->height =  height;
}

void Game::Run(){
  while(!GetState().QuitRequested()) {
    CalculateDeltaTime();
    InputManager::GetInstance().Update();
    GetState().Update(dt);
    GetState().Render();
    SDL_RenderPresent(renderer);
    SDL_Delay(33);
  }
  Resources::GetInstance().ClearMusics();
  Resources::GetInstance().ClearSounds();
  Resources::GetInstance().ClearImages();
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
    instance = new Game(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT);
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

int Game::GetWidth(){
  return width;
}

int Game::GetHeight(){
  return height;
}

void Game::CalculateDeltaTime(){
  int ticks = SDL_GetTicks();
  dt = (ticks - frameStart)/1000.0f;
  frameStart = ticks;
}

float Game::GetDeltaTime(){
  return dt;
}