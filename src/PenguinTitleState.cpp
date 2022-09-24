#include <PenguinStageState.h>
#include <Text.h>
#include <Camera.h>
#include <PenguinTitleState.h>
#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <Timer.h>

PenguinTitleState::PenguinTitleState(){
  LoadAssets();
}

PenguinTitleState::~PenguinTitleState(){}

void PenguinTitleState::Update(float dt){
  UpdateArray(dt);
  blinkingTextTimer.Update(dt);

  if(blinkingTextTimer.Get() > 0.5){
    dynamic_cast<Text*>(blinkingText->GetComponent("TEXT"))->SetText("");
  }
  if(blinkingTextTimer.Get() > 1.0){
    dynamic_cast<Text*>(blinkingText->GetComponent("TEXT"))->SetText("Press space to start");
    blinkingTextTimer.Restart();
  }

  quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);
  if (InputManager::GetInstance().KeyPress(SPACE_BAR_KEY)){
    Game::GetInstance().Push(new PenguinStageState());
  }
}

void PenguinTitleState::Resume(){
  Camera::pos = Vec2(0, 0);
}

void PenguinTitleState::Render(){
  RenderArray();
}

void PenguinTitleState::Start(){
  StartArray();
}

void PenguinTitleState::Pause(){}

void PenguinTitleState::LoadAssets(){
  GameObject *titleBackground = new GameObject(&objectArray);
  titleBackground->AddComponent(new Sprite(*titleBackground, "assets/img/title.jpg"));
  AddObject(titleBackground);

  blinkingText = new GameObject(&objectArray);
  blinkingText->AddComponent(new Text(*blinkingText, "assets/font/Call me maybe.ttf", 60, Text::TextStyle::BLENDED, "Press space to start", {0, 60, 90, 255}));
  blinkingText->box.x = Game::GetInstance().GetWidth() / 2 - blinkingText->box.w / 2;
  blinkingText->box.y = Game::GetInstance().GetHeight() - blinkingText->box.h;
}


