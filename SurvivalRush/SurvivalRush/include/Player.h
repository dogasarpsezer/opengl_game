#pragma once
#include "SimpleCharacter.h"
#include "Input.h"
#include "Weapon.h"

class Player : public SimpleCharacter
{
public:
	Player(float speed,float damping,float maxForce,float rotationSpeed);
	void PlayerMotionUpdate(const Input& input,const Camera& camera);
	void PlayerActionUpdate(const Input& input);
	void Reset();
private:
	float speed;
	float maxForce;
	Vector3 velocity;
	float damping;
	float rotationSpeed;

	Weapon* weapon[3];
};
