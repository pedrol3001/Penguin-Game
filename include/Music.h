#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include "Asset.h"
#include "Component.h"

using namespace std;

class Music : public Asset, public Component {
public:
  Music(GameObject &associated);
  Music(GameObject &associated, string file);
  ~Music();

  void Play (int times = -1);
  void Stop (int msToStop = 1500);
  void Open (string file);
  bool IsOpen();

  void Update(float dt);
  void Render();
  bool Is(string type);

private:
  Mix_Music* music;
};

#endif