#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include  "Component.h"

class CameraFollower : public Component {
public:
  CameraFollower(GameObject &associated);

  void Update(float dt);

  void Render();

  bool Is(string type);
};

#endif