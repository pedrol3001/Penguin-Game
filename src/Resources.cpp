#include <Game.h>
#include <Resources.h>
#include <SDL_exception.h>

Resources* Resources::instance = nullptr;

Resources::Resources(){}

Resources& Resources::GetInstance(){
  if(instance == nullptr){
    instance = new Resources();
  }
  return *instance;
}

SDL_Texture *Resources::GetImage(string file){
  imageTable.try_emplace(file, IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()));
  if(imageTable[file] == nullptr) throw(SDL_Exception("Failed to load sprite"));

  return imageTable[file];
}

void Resources::ClearImages(){
  for (auto& it: imageTable) SDL_DestroyTexture(it.second);
  imageTable.clear();
}

Mix_Music *Resources::GetMusic(string file){
  musicTable.try_emplace(file, Mix_LoadMUS(file.c_str()));
  if(musicTable[file] == nullptr) throw SDL_Exception("Failed to open music");

  return musicTable[file];
}

void Resources::ClearMusics(){
  for (auto& it: musicTable) Mix_FreeMusic(it.second);
  musicTable.clear();
}

Mix_Chunk *Resources::GetSound(string file){
  soundTable.try_emplace(file, Mix_LoadWAV(file.c_str()));
  if(soundTable[file] == nullptr) throw SDL_Exception("Failed to open sound");

  return soundTable[file];
}

void Resources::ClearSounds(){
  for (auto& it: soundTable) Mix_FreeChunk(it.second);
  soundTable.clear();
}

TTF_Font *Resources::GetFont(string file, int size){
  string key = file + to_string(size);
  fontTable.try_emplace(key, TTF_OpenFont(file.c_str(), size));
  if(fontTable[key] == nullptr) throw SDL_Exception("Failed to open font");

  return fontTable[key];
}

void Resources::ClearFont(){
  for (auto& it: fontTable) TTF_CloseFont(it.second);
  fontTable.clear();
}