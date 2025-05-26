#pragma once
#include "SimpleCharacter.h"
#include "SimpleGeo.h"
#include "Collider.h"
#include "Player.h"
#include "Bullet.h"
#include <list>

class Enemy:public SimpleCharacter
{
public:
	Enemy(SimpleGeo geo,float speed, float damage, float health,float maxForce,Collider collider);
	Enemy* Clone()
	{
		return new Enemy(*this);
	}
	void Move(Vector3 playerPos,std::list<Enemy*>& enemies);
	
	void Damage(float amount)
	{
		health -= amount;
	}

	bool Dead()
	{
		return health <= 0;
	}

	Collider collider;
	Vector3 velocity;
	float damage;
private:
	float speed;
	float maxForce;
	float health;
};


class EnemyManager
{
public:
	static EnemyManager& Instance();
	void Update(Player& player);
	void CreateEnemy(Vector3 position);
	void Clear()
	{
		enemies.clear();
	}
	bool CheckHits(Bullet* bullet);
	void Reset()
	{
		Clear();
		timer = 0;
	}
	float spawnNewEnemyTime;
	float spawnMinTime;
	float timeDecreasePerSpawn;


private:
	EnemyManager() = default;                    // private constructor
	EnemyManager(const EnemyManager&) = delete;         // no copying
	EnemyManager& operator=(const EnemyManager&) = delete;

	std::list<Enemy*> enemies;
	float timer;
};

