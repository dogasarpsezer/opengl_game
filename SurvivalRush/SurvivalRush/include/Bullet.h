#pragma once
#include "SimpleCharacter.h"
#include "Vector.h"
#include <list>

class Bullet : public SimpleCharacter
{
public:
	Bullet(SimpleGeo geo, float speed, float damage,float range);
	void Move();
	bool BulletUpdate();
	Bullet* Clone(Vector3 direction,Vector3 position)
	{
		Bullet* newBullet = new Bullet(*this);
		newBullet->direction = direction;
		newBullet->transform.SetPosition(position);

		float angleToRotate = SignedAngleBetween(newBullet->transform.Forward(),direction, up);
		newBullet->transform.RotateOnY(angleToRotate);

		return newBullet;
	}
	float range;

private:
	Vector3 direction;
	float speed;
	float damage;
	float totalDistance;
};

class BulletManager
{
public:
	static BulletManager& Instance();
	void Update();
	void AddBullet(Bullet* bullet);
	void Clear();
private:
	BulletManager() = default;                    // private constructor
	BulletManager(const BulletManager&) = delete;         // no copying
	BulletManager& operator=(const BulletManager&) = delete;

	std::list<Bullet*> bullets;
};
