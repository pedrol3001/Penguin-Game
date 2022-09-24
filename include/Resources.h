#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include <string>
#include <unordered_map>
#include <SDL_include.h>

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

  TTF_Font *GetFont(string file,int size);
  void ClearFont();

private:
  unordered_map<string, SDL_Texture*> imageTable;
  unordered_map<string, Mix_Music*> musicTable;
  unordered_map<string, Mix_Chunk*> soundTable;
  unordered_map<string, TTF_Font*> fontTable;
};

#endif