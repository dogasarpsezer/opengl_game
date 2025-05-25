#pragma once
#include "SimpleGeo.h"
#include "SimpleCharacter.h"
#include "Bullet.h"
#include <vector>;

class Weapon:
{
public:
	Weapon(Bullet bulletTemplate,float bulletSpeed,float fireRate);
	void Fire(Vector3 direction);
	void Update(float& deltaTime);
private:
	float bulletSpeed;
	float timer;
	float fireRate;
	Bullet bulletTemplate;
	std::vector<Bullet*> bullets;
};
