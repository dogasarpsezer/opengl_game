#include "include/Bullet.h"
#include "include/CustomTime.h"
#include "include/EnemyManager.h"
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

bool EnemyManager::CheckHits(Bullet* bullet)
{
	for (Enemy* enemy : enemies)
	{
		Vector3 p1 = enemy->transform.position;
		float r1 = enemy->collider.GetRadius(enemy->transform.scale.x);

		Vector3 p2 = bullet->transform.position;
		float r2 = bullet->collider.GetRadius(bullet->transform.scale.x);

		bool collides = CircleCollision(p1, r1, p2, r2);

		if(collides)
		{
			enemy->Damage(bullet->damage);
			return true;
		}
	}

	return false;
}


Bullet::Bullet(SimpleGeo geo, float speed, float damage, float range, Collider collider) :
	SimpleCharacter(geo), speed(speed), damage(damage), range(range), collider(collider)
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
	collider.DrawDebug(transform.position,transform.scale);

	bool hit = EnemyManager::Instance().CheckHits(this);
	if(totalDistance >= range || hit)
	{
		return true;
	}

	return false;
}
