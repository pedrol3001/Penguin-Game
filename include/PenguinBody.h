#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <Component.h>
#include <memory>
#include <Vec2.h>

class PenguinBody: public Component {
public:
  PenguinBody(GameObject& associated);
  ~PenguinBody();

  void Start();
  void NotifyCollision (GameObject& other);
  void Update(float dt);
  void Render();
  bool Is(string type);

  Vec2 Center();

  static PenguinBody* player;
private:

  weak_ptr<GameObject> pcannon;
  Vec2 speed;
  float linearSpeed;
  float angle;
  int hp;
};

#endif
