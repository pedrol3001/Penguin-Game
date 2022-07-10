#include "PenguinState.h"

#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Sound.h"
#include "Game.h"
#include "TileSet.h"
#include "TileMap.h"

PenguinState::PenguinState() : State() {
  LoadAssets();
}

PenguinState::~PenguinState() {}

void PenguinState::LoadAssets(){
  GameObject *bg = new GameObject(&objectArray);
	Sprite *backgroundSprite = new Sprite(*bg, "assets/img/ocean.jpg");
	Music *backgroundMusic = new Music(*bg, "assets/audio/stageState.ogg");
  bg->AddComponent(backgroundSprite);
	bg->AddComponent(backgroundMusic);
	backgroundMusic->Play();

	GameObject *tm = new GameObject(&objectArray);
	tm->box.x = 0;
	tm->box.y = 0;
	tm->box.w = 1024;
	tm->box.h = 600;

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

	go->box.x = mouseX - go->box.w/2;
  go->box.y = mouseY - go->box.h/2;
	go->box.w = penguinFaceSprite->GetWidth();
  go->box.h = penguinFaceSprite->GetHeight();
}

void PenguinState::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) {
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				GameObject* go = (GameObject*) objectArray[i].get();

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent("FACE");
					if ( nullptr != face ) {
						face->Damage(std::rand() % 10 + 10);
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			else {
				Vec2 objPos = Vec2( 200, 0 ).Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}