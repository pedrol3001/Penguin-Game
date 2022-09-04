#include "Game.h"
#include "Sprite.h"
#include "Resources.h"
#include "SDL_exception.h"
#include "NullGameObject.h"
#include "Camera.h"

Sprite::Sprite(string file, int frameCount, float frameTime) : Sprite(* new NullGameObject(), file, frameCount, frameTime) {}

Sprite::Sprite(GameObject& associated) : Component(associated), scale(1, 1), texture(nullptr){}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime) : Sprite(associated) {
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  Open(file);
  this->associated.box.w = width / frameCount;
  this->associated.box.h = height;
}

Sprite::~Sprite() {}

void Sprite::SetFrame (int frame) {
	currentFrame = frame;
	SetClip(currentFrame * width / frameCount, clipRect.y, width / frameCount, height);
}

void Sprite::SetFrameCount (int frameCount) {
  this->frameCount = frameCount;
  SetScale(scale.x, scale.y);
  SetFrame(0);
}

void Sprite::SetFrameTime (float frameTime) {
	this->frameTime = frameTime;
}

int Sprite::GetWidth() {
  return width * scale.x / frameCount;
}

int Sprite::GetHeight() {
  return height * scale.y;
}

void Sprite::Open(string file) {
  texture = Resources::GetInstance().GetImage(file);

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width / frameCount, height);
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
  associated.box.w = width * scaleVal / frameCount;
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

void Sprite::Update(float dt) {
  timeElapsed += dt;

	if (timeElapsed > frameTime) {
    SetFrame(currentFrame < frameCount - 1 ? currentFrame + 1 : 0);
	}
}

bool Sprite::Is(string type) {
  return type == "SPRITE";
}

