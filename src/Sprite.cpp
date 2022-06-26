#include "SDL_exception.h"
#include "Sprite.h"
#include "Game.h"

#include <iostream>
using namespace std;

Sprite::Sprite() {
  texture = nullptr;
}

Sprite::Sprite(string file) {
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite() {
  if (texture != nullptr) SDL_DestroyTexture(texture);
}

void Sprite::Open(string file) {
  if(IsOpen()) SDL_DestroyTexture(texture);
  texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
  if(texture == nullptr) throw(SDL_Exception("Failed to load sprite"));

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, GetWidth(), GetHeight());
}

bool Sprite::IsOpen(){
  return texture != nullptr;
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(int x, int y) {
  SDL_Rect rec = { x, y, width, height};

  SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &rec);
}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}
