#include <GameData.h>
#include <Text.h>
#include <Sprite.h>
#include <Camera.h>
#include <PenguinEndState.h>
#include <Game.h>
#include <PenguinTitleState.h>
#include <InputManager.h>
#include <Timer.h>

bool GameData::playerVictory;

PenguinEndState::PenguinEndState(){
  LoadAssets();
}

PenguinEndState::~PenguinEndState(){}

void PenguinEndState::LoadAssets(){
  GameObject *background = new GameObject(&objectArray);
  SDL_Color textColor;

  if(GameData::playerVictory){
    background->AddComponent(new Sprite(*background, "assets/img/win.jpg"));
    backgroundMusic.Open("assets/audio/endStateWin.ogg");
    textColor =  {0, 110, 150, 255};
  } else{
    background->AddComponent(new Sprite(*background, "assets/img/lose.jpg"));
    backgroundMusic.Open("assets/audio/endStateLose.ogg");
    textColor =  {180, 100, 120, 255};
  }

  GameObject *restartText = new GameObject(&objectArray);
  restartText->AddComponent(new Text(*restartText, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Press space to restart", textColor));
  restartText->box.y = -20;

  GameObject *orText = new GameObject(&objectArray);
  orText->AddComponent(new Text(*orText, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Or", textColor));
  orText->box.x = restartText->box.w / 2 - orText->box.w / 2;
  orText->box.y = restartText->box.h / 2 - 20;

  GameObject *exitText = new GameObject(&objectArray);
  exitText->AddComponent(new Text(*exitText, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Press ESC to exit", textColor));
  exitText->box.x = restartText->box.w / 2 - exitText->box.w / 2;
  exitText->box.y = restartText->box.h - 20;

  if(!GameData::playerVictory){
    restartText->box.x += Game::GetInstance().GetWidth() / 2 - restartText->box.w / 2;
    orText->box.x += restartText->box.x;
    exitText->box.x += restartText->box.x;
  }
}

void PenguinEndState::Update(float dt){
  UpdateArray(dt);

  quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);
  if (InputManager::GetInstance().KeyPress(SPACE_BAR_KEY)){
    popRequested = true;
    Game::GetInstance().Push(new PenguinTitleState());
  }
}

void PenguinEndState::Render(){
  RenderArray();
}

void PenguinEndState::Start(){
  StartArray();
  Camera::pos = Vec2(0, 0);
  backgroundMusic.Play();
}

void PenguinEndState::Pause(){}

void PenguinEndState::Resume(){}