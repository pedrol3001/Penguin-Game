#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.h"
#include "Music.h"
#include <memory>

class State {
public:
  State();
  virtual ~State();

  bool QuitRequested();
  void Update(float dt);
  void Render();

  void Start();
  weak_ptr<GameObject> AddObject(GameObject *go);
  weak_ptr< GameObject > GetObjectPtr(GameObject *go);

protected:
  virtual void LoadAssets() = 0;

  bool started;
  bool quitRequested;
  vector<shared_ptr<GameObject>> objectArray;
};

#endif