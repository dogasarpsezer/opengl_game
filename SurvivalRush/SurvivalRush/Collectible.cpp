#include "include/Collectible.h"
#include "include/Debug.h"

void CollectibleManager::CreateCollectible(Vector3 position)
{
	Collectible* collectible = new Collectible(SimpleGeo(CIRCLE,white,0.5f),10,5,3,6,Collider(0.25f));
	collectible->transform.SetPosition(position);
	collectibles.push_back(collectible);
}


void Collectible::Move(Vector3& playerPos)
{
	float deltaTime = CustomTime::Instance().deltaTime;
	Vector3 desiredVelocity = (playerPos - transform.position).Normalized() * speed;


	Vector3 force = desiredVelocity - velocity;
	force = force.ClampMagnitude(maxForce);

	velocity = velocity + force;
	velocity = velocity.ClampMagnitude(speed);

	Vector3 movement = velocity * deltaTime;

	transform.Move(velocity * deltaTime);
	collider.DrawDebug(transform.position, transform.scale);
}

void Collectible::CollectibleUpdate(Player& player)
{
	Vector3 playerPos = player.transform.position;
	float playerRad = player.collider.GetRadius(player.transform.scale.x);
	if(activated == false)
	{
		if (timer >= lifeTime)
		{
			destroy = true;
			return;
		}


		Vector3 scale = Vector3(1, 1, 1) * (1.0f - timer/lifeTime);
		transform.SetScale(scale);

		float distance = (transform.position - playerPos).SqrLength();
		if(distance <= collectRadius * collectRadius)
		{
			activated = true;
		}

		timer += CustomTime::Instance().deltaTime;

		SimpleCharacter* collectRad = new SimpleCharacter(SimpleGeo(CIRCLE_BOUNDS,blue,1.0f));
		collectRad->transform.SetPosition(transform.position);
		collectRad->transform.SetScale(transform.scale * collectRadius * 2);
		Debug::Instance().AddDebug(collectRad);
	}
	else
	{
		Move(playerPos);

		Vector3 p1 = transform.position;
		float r1 = collider.GetRadius(transform.scale.x);

		bool collides = CircleCollision(p1, r1, playerPos, playerRad);
		if (collides)
		{
			player.Heal(5);
			destroy = true;
		}
	}
}

void CollectibleManager::Update(Player& player)
{
	for (Collectible* collectible : collectibles)
	{
		collectible->CollectibleUpdate(player);
		collectible->Update();
	}


	for (auto it = collectibles.begin(); it != collectibles.end(); )
	{
		Collectible* collectible = *it;

		bool destroy = collectible->destroy;
		if (destroy)
		{
			delete collectible;
			it = collectibles.erase(it); // O(1) in list, no shifting
		}
		else
		{
			++it;
		}
	}
}
