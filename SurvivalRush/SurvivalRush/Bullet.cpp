#include "include/Bullet.h"
#include "include/CustomTime.h"
#include <iostream>

BulletManager& BulletManager::Instance()
{
	static BulletManager instance; // only created once
	return instance;
}

void BulletManager::Update()
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		Bullet* bullet = *it;

		bullet->Move();
		bullet->Update();

		bool destroy = bullet->BulletUpdate();

		if (destroy)
		{
			delete bullet;
			it = bullets.erase(it); // O(1) in list, no shifting
		}
		else
		{
			++it;
		}
	}
}

void BulletManager::AddBullet(Bullet* bullet)
{
	bullets.push_back(bullet);
}

void BulletManager::Clear()
{
	for (Bullet* bullet:bullets)
	{
		delete bullet;
	}

	bullets.clear();
}


Bullet::Bullet(SimpleGeo geo,float speed, float damage,float range) : 
	SimpleCharacter(geo),speed(speed),damage(damage), range(range)
{
}

void Bullet::Move()
{
	float deltaTime = CustomTime::Instance().deltaTime;
	float moveAmount = speed * deltaTime;
	totalDistance += moveAmount;

	Vector3 movement = direction.Normalized() * moveAmount;
	transform.Move(movement);

	float scaleT = 1.0f - totalDistance / range;
	transform.SetScale(Vector3(scaleT,scaleT,scaleT));
}

bool Bullet::BulletUpdate()
{
	if(totalDistance >= range)
	{
		return true;
	}

	return false;
}
