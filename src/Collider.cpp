#include "Collider.h"
#include "GameObject.h"
#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>
#include <math.h>

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider (GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {}

void Collider::Update (float dt) {
	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	box.x = associated.box.Center().x + offset.Rotate(associated.angleDeg * M_PI / 180).x - box.w / 2;
	box.y = associated.box.Center().y + offset.Rotate(associated.angleDeg * M_PI / 180).y - box.h / 2;
}

void Collider::SetScale (Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset (Vec2 offset) {
	this->offset = offset;
}

bool Collider::Is (string type) {
	return type == "COLLIDER";
}

void Collider::Render () {
#ifdef DEBUG
  Vec2 center( box.Center() );
  SDL_Point points[5];

  Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg / (180 / M_PI)) + center - Camera::pos;

  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180 / M_PI) ) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180 / M_PI) ) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180 / M_PI) ) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

bool Collider::IsColliding(Collider* a) {
  Vec2 A[] = { Vec2( a->box.x, a->box.y + a->box.h ),
          Vec2( a->box.x + a->box.w, a->box.y + a->box.h ),
          Vec2( a->box.x + a->box.w, a->box.y ),
          Vec2( a->box.x, a->box.y )
        };
  Vec2 B[] = { Vec2( box.x, box.y + box.h ),
          Vec2( box.x + box.w, box.y + box.h ),
          Vec2( box.x + box.w, box.y ),
          Vec2( box.x, box.y )
        };

  for (auto& v : A) {
    v = (v - a->box.Center()).Rotate(a->associated.angleDeg * M_PI / 180) + a->box.Center();
  }

  for (auto& v : B) {
    v = (v - box.Center()).Rotate(associated.angleDeg * M_PI / 180) + box.Center();
  }

  Vec2 axes[] = { (A[0] - A[1]).Normalized(), (A[1] - A[2]).Normalized(), (B[0] - B[1]).Normalized() , (B[1] - B[2]).Normalized() };

  for (auto& axis : axes) {
    float P[4];

    for (int i = 0; i < 4; ++i) P[i] = A[i].Dot(axis);

    float minA = *std::min_element(P, P + 4);
    float maxA = *std::max_element(P, P + 4);

    for (int i = 0; i < 4; ++i) P[i] = B[i].Dot(axis);

    float minB = *std::min_element(P, P + 4);
    float maxB = *std::max_element(P, P + 4);

    if (maxA < minB || minA > maxB)
      return false;
  }

  return true;
}

