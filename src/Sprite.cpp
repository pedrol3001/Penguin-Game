#include "Game.h"
#include "Sprite.h"
#include "Resources.h"
#include "SDL_exception.h"
#include "NullGameObject.h"
#include "Camera.h"

Sprite::Sprite(string file) : Sprite(* new NullGameObject(), file) {}

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr){}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated) {
  Open(file);
}

Sprite::~Sprite() {}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}

void Sprite::Open(string file) {
  texture = Resources::GetInstance().GetImage(file);

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
  Render(static_cast<int>(associated.box.x - Camera::pos.x), static_cast<int>(associated.box.y - Camera::pos.y));
}

void Sprite::Render(int x, int y) {
  SDL_Rect rec = {x, y, clipRect.w, clipRect.h};

  SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &rec);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) {
  return type == "SPRITE";
}

