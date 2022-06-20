#ifndef ERROR_HPP
#define ERROR_HPP

#define INCLUDE_SDL
#include "SDL_include.h"

#include <string>
#include <iostream>

using namespace std;

class SDL_Exception : public exception {
public:
  SDL_Exception();
  SDL_Exception(string msg);
  const char* What();
  void Log();

private:
  string message;
};

#endif