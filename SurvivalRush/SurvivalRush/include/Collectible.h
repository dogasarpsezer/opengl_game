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
	Collectible(SimpleGeo geo,float speed,float maxForce,float collectRadius,float lifeTime,Collider collider) :
		SimpleCharacter(geo),collider(collider),speed(speed), 
		maxForce(maxForce),lifeTime(lifeTime), collectRadius(collectRadius) 
	{
		timer = 0;
	}
	
	Collectible* Clone()
	{
		return new Collectible(*this);
	}

	void Move(Vector3& playerPos);
	void CollectibleUpdate(Player& player);

	Collider collider;
	Vector3 velocity;
	bool destroy = false;
	bool activated = false;
private:
	float lifeTime;
	float collectRadius;
	float timer;
	float speed;
	float maxForce;
};


class CollectibleManager
{
public:
	static CollectibleManager& Instance()
	{
		static CollectibleManager instance; // only created once
		return instance;
	}
	void Update(Player& player);
	void CreateCollectible(Vector3 position);
	void Clear()
	{
		for (Collectible* collectible: collectibles)
		{
			delete collectible;
		}

		collectibles.clear();
	}

	void Reset()
	{
		Clear();
	}

private:
	CollectibleManager() = default;                    // private constructor
	CollectibleManager(const CollectibleManager&) = delete;         // no copying
	CollectibleManager& operator=(const CollectibleManager&) = delete;
	std::list<Collectible*> collectibles;
};

