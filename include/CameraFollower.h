#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include  "Component.h"

#define CAMERA_FOLLOWER_TYPE "CameraFollower"

class CameraFollower : public Component {
public:
  CameraFollower(GameObject &associated);

  void Update(float dt);

  void Render();

  bool Is(string type);
};

#endif