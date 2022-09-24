#include <SDL_exception.h>
#include <Music.h>
#include <Resources.h>
#include <NullGameObject.h>

Music::Music() : Music(* new NullGameObject()) {}

Music::Music(GameObject &associated) : Component(associated), music(nullptr){}

Music::Music(GameObject &associated, string file) : Component(associated), music(nullptr){
  Open(file);
}

Music::~Music(){
  Stop(0);
}

void Music::Play(int times){
  if (music == nullptr) throw SDL_Exception("Failed to play music");

  Mix_PlayMusic(music, times);
}

void Music::Stop(int ms){
  Mix_FadeOutMusic(ms);
}

void Music::Open(string file){
  music = Resources::GetInstance().GetMusic(file);
}

bool Music::IsOpen(){
  return music != nullptr;
}

void Music::Update(float dt){}

void Music::Render(){}

bool Music::Is(string type){
  return type == "MUSIC";
}