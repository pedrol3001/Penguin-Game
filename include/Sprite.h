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
  Sprite(string file);
  Sprite(GameObject& associated);
  Sprite(GameObject& associated, string file);
  ~Sprite();

  void Open(string file);
  bool IsOpen();

  void SetClip(int x, int y, int w, int h);
  int GetWidth();
  int GetHeight();

  void Render();
  void Render(int x, int y);
  void Update(float dt);
  bool Is(string type);

  void SetScaleX(float scaleVal);
  void SetScaleY(float scaleVal);
  void SetScale(float scaleX, float scaleY);
  Vec2 GetScale();

private:
  int width;
  int height;
  Vec2 scale;
  SDL_Rect clipRect;
  SDL_Texture* texture;
};

#endif