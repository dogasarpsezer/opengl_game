#pragma once
#include "SimpleGeo.h"
#include "SimpleCharacter.h"
#include "Bullet.h"
#include <list>;

class Weapon
{
public:
	Weapon(Bullet bulletTemplate,float fireRate);
	virtual void Fire(Vector3 direction,Vector3 firePos);
	void Update();

	Weapon* Clone() const
	{
		return new Weapon(*this);
	}

protected:
	float bulletSpeed;
	float timer;
	float fireRate;
	Bullet bulletTemplate;
};

class WeaponShotgun : public Weapon
{
public:
	WeaponShotgun(Bullet bulletTemplate, float fireRate,int bulletCount,float bulletSpread);
	void Fire(Vector3 direction,Vector3 firePos) override;

	WeaponShotgun* Clone() const
	{
		return new WeaponShotgun(*this);
	}
private:
	int bulletCount;
	float bulletSpread;
};
