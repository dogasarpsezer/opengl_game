#include "include/Weapon.h"
#include "include/CustomTime.h"
#include <iostream>


Weapon::Weapon(Bullet bulletTemplate, float fireRate) :
	bulletTemplate(bulletTemplate),fireRate(fireRate)
{
    timer = 0;
}


void Weapon::Fire(Vector3 direction,Vector3 firePos)
{
	if (timer >= fireRate)
	{
		Bullet* bullet = bulletTemplate.Clone(direction,firePos);
        BulletManager::Instance().AddBullet(bullet);
		timer = 0;
	}
}

void Weapon::Update()
{
    timer += CustomTime::Instance().deltaTime;
}


WeaponShotgun::WeaponShotgun(Bullet bulletTemplate, float fireRate, int bulletCount, float bulletSpread) :
	Weapon(bulletTemplate, fireRate), bulletCount(bulletCount),bulletSpread(bulletSpread)
{
}

void WeaponShotgun::Fire(Vector3 direction,Vector3 firePos)
{
    if (timer >= fireRate)
    {
        Vector3 currentDirection = direction.RotateY(((bulletCount - 1) * -bulletSpread / 2.0f));
        //Fire
        for (size_t i = 0; i < bulletCount; i++)
        {
            Bullet* bullet = bulletTemplate.Clone(currentDirection, firePos);
            BulletManager::Instance().AddBullet(bullet);

            currentDirection = currentDirection.RotateY(bulletSpread);
        }
        timer = 0;
    }
}
