#include "PenguinState.h"

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Game.h"
#include "TileSet.h"
#include "InputManager.h"
#include "TileMap.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

PenguinState::PenguinState() : State() {
	LoadAssets();

	GameObject *alien = new GameObject(&objectArray);
	alien->AddComponent(new Alien(*alien, 5));
	alien->box += Vec2(512 + alien->box.w/2, 200 + alien->box.h/2);
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

	GameObject *tile = new GameObject(&objectArray);
	tile->box.x = 0;
	tile->box.y = 0;
	tile->box.w = Game::GetInstance().GetWidth();
	tile->box.h = Game::GetInstance().GetHeight();;

	TileSet *set = new TileSet(64, 64, "assets/img/tileset.png");
	TileMap *map = new TileMap(*tile, "assets/map/tileMap.txt", set);
	tile->AddComponent(map);
}