#ifndef FACE_H
#define FACE_H

#include "Component.h"

class Face : public Component {
public:
  Face(GameObject &associated);

  void Damage(int damage);

  void Update(float dt);
  void Render();
  bool Is(string type);

private:
  int hitPoints;
};


#endif