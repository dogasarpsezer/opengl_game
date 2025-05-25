#pragma once
#include "SimpleCharacter.h"
#include "Input.h"

class Player : public SimpleCharacter
{
public:
	Player(float speed,float damping,float maxForce,float rotationSpeed);
	void PlayerMotionUpdate(const Input& input,const Camera& camera);
private:
	float speed;
	float maxForce;
	Vector3 velocity;
	float damping;
	float rotationSpeed;
};
