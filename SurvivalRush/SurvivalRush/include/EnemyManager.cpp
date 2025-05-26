#include "EnemyManager.h"
#include "CustomTime.h"
#include "Player.h"
#include "CustomMath.h"

Enemy::Enemy(SimpleGeo geo, float speed, float damage,float health, float maxForce,Collider collider)
	: SimpleCharacter(geo), speed(speed), damage(damage), maxForce(maxForce),collider(collider), health(health)
{
}

void Enemy::Move(Vector3 position,std::list<Enemy*>& enemies)
{
	float deltaTime = CustomTime::Instance().deltaTime;
	Vector3 desiredVelocity = (position - transform.position).Normalized() * speed;


	Vector3 force = desiredVelocity - velocity;
	force = force.ClampMagnitude(maxForce);

	velocity = velocity + force;
	velocity = velocity.ClampMagnitude(speed);

	Vector3 movement = velocity * deltaTime;
	for (Enemy* other : enemies)
	{
		if (other == this) continue;

		Vector3 p1 = transform.position + movement;
		Vector3 p2 = other->transform.position;

		float r1 = collider.GetRadius(transform.scale.x);
		float r2 = other->collider.GetRadius(transform.scale.x);
		bool collides = CircleCollision(p1,r1,p2,r2);

		if (collides)
		{
			Vector3 dir = (p1 - p2).Normalized();
			velocity = velocity + dir * 1;

			other->velocity = other->velocity - dir * 1;
		}
	}

	transform.Move(velocity * deltaTime);
	collider.DrawDebug(transform.position,transform.scale);
}

EnemyManager& EnemyManager::Instance()
{
	static EnemyManager instance; // only created once
	return instance;
}

void EnemyManager::CreateEnemy(Vector3 position)
{
	Enemy* newEnemy = new Enemy(SimpleGeo(SQUARE,black),5,10,25,8,Collider(0.5f));
	newEnemy->transform.SetPosition(position);
	enemies.push_back(newEnemy);
}

void EnemyManager::Update(Player& player)
{
	Vector3 playerPos = player.transform.position;
	float deltaTime = CustomTime::Instance().deltaTime;

	timer += deltaTime;

	if(timer >= spawnNewEnemyTime)
	{
		float randomAngle = RandomFloat(0.0f,360.0f);
		Vector3 dir = forward;

		dir.RotateY(randomAngle);
		
		float randomRange = RandomFloat(10, 15);

		CreateEnemy(playerPos + dir * randomRange);
		spawnNewEnemyTime -= timeDecreasePerSpawn;

		spawnNewEnemyTime = Clamp(spawnNewEnemyTime, spawnMinTime, 10000.0f);
		timer = 0.0f;
	}

	float playerRad = player.collider.GetRadius(player.transform.scale.x);
	for (Enemy* enemy:enemies)
	{
		if(enemy->Dead() == false)
		{
			enemy->Move(playerPos, enemies);
			enemy->Update();

			Vector3 p1 = enemy->transform.position;
			float r1 = enemy->collider.GetRadius(enemy->transform.scale.x);

			bool collides = CircleCollision(p1, r1, playerPos, playerRad);
			if (collides)
			{
				enemy->Damage(10000);
				player.Damage(enemy->damage);
			}
		}
	}

	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		Enemy* enemy = *it;

		bool destroy = enemy->Dead();
		if (destroy)
		{
			delete enemy;
			it = enemies.erase(it); // O(1) in list, no shifting
		}
		else
		{
			++it;
		}
	}
}
