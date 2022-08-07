#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <unordered_map>

#include "Vec2.h"

#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define SPACE_BAR_KEY       SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

using namespace std;

class InputManager {
public:
  InputManager();
  ~InputManager();

  static InputManager& GetInstance();

  void Update();

  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);

  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);

  int GetMouseX();
  int GetMouseY();
  Vec2 GetMouse();

  bool QuitRequested();

private:
  bool mouseState[6];
  int mouseUpdate[6];

  unordered_map<int, bool> keyState;
  unordered_map<int, int> keyUpdate;

  bool quitRequested;

  int updateCounter;

  int mouseX;
  int mouseY;
};


#endif