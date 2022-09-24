#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE

#include <SDL_include.h>

#include <string>
#include <Asset.h>
#include <Component.h>
#include <Timer.h>

using namespace std;

class Sprite : public Asset, public Component {
public:
  Sprite(GameObject& associated);
  Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
  Sprite(string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

  ~Sprite();

  void SetFrame(int frame);
  void SetFrameCount(int frameCount);
  void SetFrameTime(float frameTime);

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

  int frameCount;
  int currentFrame;
  float timeElapsed;
  float frameTime;

  Timer selfDestructCount;
  float secondsToSelfDestruct = 0;
};

#endif