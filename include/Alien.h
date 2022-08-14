#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include "Component.h"

class Alien : public Component {
public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(string type);

private:
  class Action{
  public:
    enum ActionType{ MOVE, SHOOT };
    Action(ActionType type, float x, float y);

    ActionType type;
    Vec2 pos;
  };

  Vec2 speed;
  int hp;

  queue<Action> taskQueue;
  vector<weak_ptr<GameObject>> minionArray;
};

#endif