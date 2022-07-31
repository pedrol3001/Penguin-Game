#include "PenguinState.h"

#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Sound.h"
#include "Game.h"
#include "TileSet.h"
#include "InputManager.h"
#include "TileMap.h"
#include "Camera.h"
#include "CameraFollower.h"

PenguinState::PenguinState() : State() {
  LoadAssets();
}

PenguinState::~PenguinState() {}

void PenguinState::LoadAssets(){
  GameObject *bg = new GameObject(&objectArray);
	Sprite *backgroundSprite = new Sprite(*bg, "assets/img/ocean.jpg");
	Music *backgroundMusic = new Music(*bg, "assets/audio/stageState.ogg");
	CameraFollower *camera = new CameraFollower(*bg);
  bg->AddComponent(backgroundSprite);
	bg->AddComponent(backgroundMusic);
	bg->AddComponent(camera);

	backgroundMusic->Play();

	GameObject *tm = new GameObject(&objectArray);
	tm->box.x = 0;
	tm->box.y = 0;
	tm->box.w = Game::GetInstance().GetWidth();
	tm->box.h = Game::GetInstance().GetHeight();;

	TileSet *set = new TileSet(64, 64, "assets/img/tileset.png");
	TileMap *map = new TileMap(*tm, "assets/map/tileMap.txt", set);
	tm->AddComponent(map);
}

void PenguinState::AddObject(int mouseX, int mouseY) {
  GameObject *go = new GameObject(&objectArray);

	Sprite *penguinFaceSprite =  new Sprite(*go, "assets/img/penguinface.png");
	Sound *boomSound = new Sound(*go, "assets/audio/boom.wav");
	Face *penguinFace = new Face(*go);

  go->AddComponent(penguinFaceSprite);
  go->AddComponent(boomSound);
  go->AddComponent(penguinFace);

	go->box.x = mouseX + Camera::pos.x - go->box.w / 2;
	go->box.y = mouseY + Camera::pos.y - go->box.h / 2;
	go->box.w = penguinFaceSprite->GetWidth();
  go->box.h = penguinFaceSprite->GetHeight();
}

void PenguinState::Input() {
	InputManager inputManager = InputManager::GetInstance();
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	int mouseX = inputManager.GetMouseX();
	int mouseY = inputManager.GetMouseY();

  if(inputManager.KeyPress(SPACE_BAR_KEY)){
    Vec2 objPos = Vec2(200, 0).Rotate((float) (-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY);
		AddObject(objPos.x, objPos.y);
  }
}