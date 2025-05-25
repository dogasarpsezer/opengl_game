#include "include/Weapon.h"


Weapon::Weapon(Bullet bulletTemplate, float bulletSpeed, float fireRate) :
	bulletTemplate(bulletTemplate),bulletSpeed(bulletSpeed),fireRate(fireRate)
{
}

void Weapon::Fire(Vector3 direction)
{
	if (timer >= fireRate)
	{
		//Fire
		timer = 0;
	}
}

void Weapon::Update(float& deltaTime)
{
	timer += deltaTime;

	for (Bullet* bullet : bullets)
	{
		
	}
}
