#ifndef SPRITE_HPP
#define SPRITE_HPP

#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"

#include <string>
#include "Asset.h"
#include "Component.h"

using namespace std;

class Sprite : public Asset, public Component {
public:
  Sprite(GameObject& associated);
  Sprite(GameObject& associated, string file);
  ~Sprite();

  void Open(string file);
  bool IsOpen();

  void SetClip(int x, int y, int w, int h);
  int GetWidth();
  int GetHeight();

  void Render();
  void Update(float dt);
  bool Is(string type);

private:
  SDL_Texture* texture;
  int width;
  int height;
  SDL_Rect clipRect;
};

#endif