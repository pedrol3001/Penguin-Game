#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include "Component.h"
#include "Timer.h"

class Alien : public Component {
public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();

  void Start();
  void NotifyCollision (GameObject& other);
  void Update(float dt);
  void Render();
  bool Is(string type);

  static int alienCount;
private:
  Vec2 speed;
  int hp;

  vector<weak_ptr<GameObject>> minionArray;

  enum AlienState {MOVING, RESTING};
  AlienState state;
  Timer restTimer;
  Vec2 destination;
};

#endif