#include "SDL_exception.h"
#include "Sprite.h"
#include "Game.h"
#include "NullGameObject.h"

Sprite::Sprite(string file) : Sprite(* new NullGameObject(), file) {}

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr){}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated) {
  Open(file);
}

Sprite::~Sprite() {
  if (texture != nullptr) SDL_DestroyTexture(texture);
}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}

void Sprite::Open(string file) {
  if(IsOpen()) SDL_DestroyTexture(texture);
  texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
  if(texture == nullptr) throw(SDL_Exception("Failed to load sprite"));

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width, height);
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

void Sprite::Render() {
  Render(static_cast<int>(associated.box.x), static_cast<int>(associated.box.y));
}

void Sprite::Render(int x, int y) {
  SDL_Rect rec = {x, y, clipRect.w, clipRect.h};

  SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &rec);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) {
  return type == "SPRITE";
}

