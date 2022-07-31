#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

#define CAMERA_SPEED 300

class Camera {
public:
  static void Follow(GameObject *newFocus);
  static void Unfollow();
  static void Update(float dt);

  static Vec2 pos;
  static Vec2 speed;

private:
  static GameObject *focus;

};

#endif