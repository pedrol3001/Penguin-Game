#include <Sound.h>
#include <Resources.h>
#include <SDL_exception.h>

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr){}

Sound::Sound(GameObject &associated, string file) : Sound(associated){
  Open(file);
}

Sound::~Sound(){
  Stop();
}

void Sound::Play(int times){
  channel = Mix_PlayChannel(-1, chunk, times - 1);
  if(channel == -1) throw SDL_Exception("Failed to play sound");
}

void Sound::Stop(){
  if(chunk != nullptr) Mix_HaltChannel(channel);
}

void Sound::Open(string file){
  chunk = Resources::GetInstance().GetSound(file);
}

bool Sound::IsOpen(){
  return chunk != nullptr;
}

void Sound::Update(float dt){}

void Sound::Render(){}

bool Sound::Is(string type){
  return type == "SOUND";
}
