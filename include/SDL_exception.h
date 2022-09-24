#ifndef ERROR_H
#define ERROR_H

#define INCLUDE_SDL
#include <SDL_include.h>

#include <string>

using namespace std;

class SDL_Exception : public exception {
public:
  SDL_Exception();
  SDL_Exception(string msg);
  const char* what();

private:
  string message;
};

#endif