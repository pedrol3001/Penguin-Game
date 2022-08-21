#include "Game.h"
#include "Sprite.h"
#include "Resources.h"
#include "SDL_exception.h"
#include "NullGameObject.h"
#include "Camera.h"

Sprite::Sprite(string file) : Sprite(* new NullGameObject(), file) {}

Sprite::Sprite(GameObject& associated) : Component(associated), scale(1, 1), texture(nullptr){}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated) {
  Open(file);
  associated.box.w = width;
  associated.box.h = height;
}

Sprite::~Sprite() {}

int Sprite::GetWidth() {
  return width * scale.x;
}

int Sprite::GetHeight() {
  return height * scale.y;
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

void Sprite::SetScaleX(float scaleVal){
  scale.x = scaleVal;
  associated.box.w = width * scaleVal;
  associated.box.x = associated.box.Center().x - associated.box.w / 2;
}
void Sprite::SetScaleY(float scaleVal){
  scale.y = scaleVal;
  associated.box.h = height * scaleVal;
  associated.box.y = associated.box.Center().y - associated.box.h / 2;
}

void Sprite::SetScale(float scaleX, float scaleY) {
  if(scaleX != 0) SetScaleX(scaleX);
  if(scaleY != 0) SetScaleY(scaleY);
}

void Sprite::Render() {
  Render(static_cast<int>(associated.box.x - Camera::pos.x), static_cast<int>(associated.box.y - Camera::pos.y));
}

void Sprite::Render(int x, int y) {
  SDL_Rect rec(x, y, static_cast<int>(clipRect.w * scale.x), static_cast<int>(clipRect.h * scale.y));
  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &rec, associated.angleDeg, nullptr , SDL_FLIP_NONE);
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) {
  return type == "SPRITE";
}

