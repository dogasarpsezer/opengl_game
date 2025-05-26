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
	Collider collider;
private:
	float speed;
	float maxForce;
	Vector3 velocity;
	float damping;
	float rotationSpeed;
	float health;
	float maxHealth;

	Weapon* weapon[3];
};
