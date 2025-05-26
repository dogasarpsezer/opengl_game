#pragma once
#include "SimpleCharacter.h"
#include "SimpleGeo.h"
#include "Collider.h"
#include "Player.h"
#include "Bullet.h"
#include <list>

class Collectible: public SimpleCharacter
{
public:
	Collectible(SimpleGeo geo,float speed,float maxForce,float collectRadius,float lifeTime,Collider collider);
	Collectible* Clone()
	{
		return new Enemy(*this);
	}

	void Move(Vector3 playerPos);

	Collider collider;
	Vector3 velocity;
	bool destroy;
	bool activated;
private:
	float lifeTime;
	float timer;
	float speed;
	float maxForce;
};


class CollectibleManager
{
public:
	static CollectibleManager& Instance();
	void Update(Player& player);
	void CreateCollectible(Vector3 position);
	void Clear();

private:
	CollectibleManager() = default;                    // private constructor
	CollectibleManager(const CollectibleManager&) = delete;         // no copying
	CollectibleManager& operator=(const CollectibleManager&) = delete;
	std::list<Collectible*> collectibles;
};

