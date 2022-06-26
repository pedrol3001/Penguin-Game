#ifndef MUSIC_HPP
#define MUSIC_HPP

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

#include <string>
#include "Asset.h"

using namespace std;

class Music : public Asset {
public:
  Music();
  Music(string file);
  ~Music();

  void Play (int times = -1);
  void Stop (int msToStop = 1500);
  void Open (string file);
  bool IsOpen();

private:
  Mix_Music* music;
};

#endif