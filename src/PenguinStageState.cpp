#include <PenguinStageState.h>
#include <Sprite.h>
#include <TileSet.h>
#include <Sound.h>
#include <Game.h>
#include <Music.h>
#include <Camera.h>
#include <TileMap.h>
#include <InputManager.h>
#include <Alien.h>
#include <PenguinEndState.h>
#include <CameraFollower.h>
#include <PenguinBody.h>
#include <GameData.h>

PenguinStageState::PenguinStageState() : StageState(){
	LoadAssets();

	GameObject *penguin = new GameObject(&objectArray);
	penguin->box.x = 704 + penguin->box.w / 2;
	penguin->box.y = 640 + penguin->box.h / 2;;
	penguin->AddComponent(new PenguinBody(*penguin));

	for(int i = 0; i < 5; i++) {
		GameObject *alien = new GameObject(&objectArray);
		alien->box.x = (rand() % MAP_WIDTH) + alien->box.w / 2;
		alien->box.y = (rand() % MAP_HEIGHT) + alien->box.h / 2;
		alien->AddComponent(new Alien(*alien, 5));
	}

	Camera::Follow(penguin);
}

PenguinStageState::~PenguinStageState(){}

void PenguinStageState::LoadAssets(){
  GameObject *bg = new GameObject(&objectArray);
	bg->AddComponent(new CameraFollower(*bg));
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));

	Music* backgroundMusic = new Music(*bg, "assets/audio/stageState.ogg");
	bg->AddComponent(backgroundMusic);
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

void PenguinStageState::UpdateGameData(){
	if(Alien::alienCount == 0){
		GameData::playerVictory = true;

		popRequested = true;
		Game::GetInstance().Push(new PenguinEndState());
	}

	if (PenguinBody::player == nullptr) {
		GameData::playerVictory = false;

		popRequested = true;
		Game::GetInstance().Push(new PenguinEndState());
	}
}
