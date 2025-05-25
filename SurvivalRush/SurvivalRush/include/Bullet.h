#pragma once
#include "SimpleCharacter.h"
#include "Vector.h"

class Bullet : public SimpleCharacter
{
public:
	Bullet(SimpleGeo geo,Vector3 direction, float speed, float damage);
	void Move();
private:
	Vector3 direction;
	float speed;
	float damage;
};
