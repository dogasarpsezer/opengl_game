#pragma once
#include "SimpleCharacter.h"
#include "Input.h"
#include "Weapon.h"
#include "Collider.h"

class Player : public SimpleCharacter
{
public:
	Player(float health,float speed,float damping,float maxForce,float rotationSpeed,Collider collider);
	void PlayerMotionUpdate(const Input& input,const Camera& camera);
	void PlayerActionUpdate(const Input& input);
	void Reset();
	void Damage(float amount)
	{
		health -= amount;
	}

	bool Dead()
	{
		return health <= 0;
	}

	void Heal(float amount)
	{
		health += amount;
		if(health > maxHealth)
		{
			health = maxHealth;
		}


	}

	Collider collider;
	float health;
	float maxHealth;
private:
	float speed;
	float maxForce;
	Vector3 velocity;
	float damping;
	float rotationSpeed;


	Weapon* weapon[3];
};
