#include <InputManager.h>
#include <Camera.h>

InputManager& InputManager::GetInstance(){
  static InputManager inputManager;
  return inputManager;
}

InputManager::InputManager() : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0){
  memset(mouseUpdate, 0, sizeof(mouseUpdate));
  memset(mouseState, 0, sizeof(mouseState));
}

InputManager::~InputManager() = default;

void InputManager::Update(){
  SDL_GetMouseState(&mouseX, &mouseY);
  updateCounter++;

  SDL_Event event;
  while (SDL_PollEvent(&event)){
    if((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat){
      keyState[event.key.keysym.sym] = (event.type == SDL_KEYDOWN);
      keyUpdate[event.key.keysym.sym] = updateCounter;
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP){
      mouseState[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN);
      mouseUpdate[event.button.button] = updateCounter;
    }
    if(event.type == SDL_QUIT){
      quitRequested = true;
    }
  }
}

bool InputManager::KeyPress(int key){
return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key){
  return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key){
  return keyState[key];
}

bool InputManager::MousePress(int button){
  return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button){
  return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button){
  return mouseState[button];
}

int InputManager::GetMouseX(){
  return mouseX;
}

int InputManager::GetMouseY(){
  return mouseY;
}

bool InputManager::QuitRequested(){
  return quitRequested;
}