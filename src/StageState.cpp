#include <StageState.h>
#include <Camera.h>
#include <Collider.h>
#include <InputManager.h>

StageState::StageState() : State(){}

StageState::~StageState(){
  objectArray.clear();
}

void StageState::Update(float dt){
  Camera::Update(dt);
  UpdateArray(dt);

  quitRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested();
  for (long unsigned int i = 0; i < objectArray.size(); i++){
    Collider* A = dynamic_cast<Collider*>(objectArray[i]->GetComponent("COLLIDER"));
		if (A == nullptr) continue;

    for (long unsigned int j = i + 1; j < objectArray.size(); j++ ){
      Collider* B = dynamic_cast<Collider*>(objectArray[j]->GetComponent("COLLIDER"));
      if (B == nullptr) continue;

      if (A->IsColliding(B)){
        objectArray[i]->NotifyCollision(*objectArray[j].get());
        objectArray[j]->NotifyCollision(*objectArray[i].get());
      }
    }
	}

  UpdateGameData();
}

void StageState::Render(){
  for(long unsigned int i = 0; i < objectArray.size(); i++) objectArray[i]->Render();
}

void StageState::Start(){
  StartArray();
}

void StageState::Pause(){}

void StageState::Resume(){}