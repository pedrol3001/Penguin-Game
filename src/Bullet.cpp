#include <Bullet.h>

#include <Sprite.h>
#include <Collider.h>

Bullet::Bullet(
  GameObject &associated,
  float angle,
  float speed,
  int damage,
  float maxDistance,
  string sprite,
  int frameCount,
  float frameTime,
  bool targetsPlayer
  ) : Component(associated), targetsPlayer(targetsPlayer), distanceLeft(maxDistance), damage(damage){


  associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
  associated.AddComponent(new Collider(associated));

  this->speed = Vec2(speed, 0).Rotate(angle);
  associated.angleDeg = angle * 180 / M_PI;
}

void Bullet::Update(float dt){
  Vec2 speedVal = speed * dt;
  associated.box += speedVal;
  distanceLeft -= speedVal.Magnitude();
  if(distanceLeft <= 0) associated.RequestDelete();
}

int Bullet::GetDamage(){
  return damage;
}

bool Bullet::IsTargetingPlayer(){
  return targetsPlayer;
}

void Bullet::NotifyCollision(GameObject& other){
  if ((other.GetComponent("ALIEN") && !targetsPlayer) || (other.GetComponent("PENGUIN_BODY") && targetsPlayer)){
		associated.RequestDelete();
	}
}

void Bullet::Render(){}

bool Bullet::Is(string type){
  return type == "BULLET";
}
