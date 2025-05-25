#include "include/Bullet.h"
#include "include/CustomTime.h"

Bullet::Bullet(SimpleGeo geo, Vector3 direction, float speed, float damage) : 
	SimpleCharacter(geo),direction(direction),speed(speed),damage(damage)
{
}

void Bullet::Move()
{
	float deltaTime = CustomTime::Instance().deltaTime;
	Vector3 movement = direction * (speed * deltaTime);

	transform.Move(movement);
}
