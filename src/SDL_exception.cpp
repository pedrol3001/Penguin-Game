#include "SDL_exception.h"

SDL_Exception::SDL_Exception(){
  const char* sdl_msg = SDL_GetError();
  message = string(sdl_msg);
}

SDL_Exception::SDL_Exception(string msg){
  const char* sdl_msg = SDL_GetError();
  message = (msg + " - " + string(sdl_msg));
}

const char* SDL_Exception::What () {
  return message.c_str();
}

void SDL_Exception::Log(){
  cout << What() << endl;
}