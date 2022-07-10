#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <string>
#include <unordered_map>
#include "SDL_include.h"

using namespace std;

class Resources {
private:
  Resources();
  static Resources* instance;
public:
  static Resources& GetInstance();
  Resources(Resources &other) = delete;
  void operator=(const Resources &) = delete;

  SDL_Texture* GetImage(string file);
  void ClearImages();

  Mix_Music* GetMusic(string file);
  void ClearMusics();

  Mix_Chunk* GetSound(string file);
  void ClearSounds();

private:
  unordered_map<string, SDL_Texture*> imageTable;
  unordered_map<string, Mix_Music*> musicTable;
  unordered_map<string, Mix_Chunk*> soundTable;
};

#endif