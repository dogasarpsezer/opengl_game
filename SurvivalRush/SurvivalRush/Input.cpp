#include "include/Input.h"
#include "include/Plane.h"
#include <iostream>

Input::Input(){}

void Input::GetKeyboardInputDown(unsigned char key)
{
	if (key == up)
	{
		upFlag = true;
	}

	if (key == down)
	{
		downFlag = true;
	}

	if (key == right)
	{
		rightFlag = true;
	}

	if (key == left)
	{
		leftFlag = true;
	}
}

void Input::GetKeyboardInputUp(unsigned char key)
{
	if (key == up)
	{
		upFlag = false;
	}

	if (key == down)
	{
		downFlag = false;
	}

	if (key == right)
	{
		rightFlag = false;
	}

	if (key == left)
	{
		leftFlag = false;
	}
}

float Input::GetKeyboardDirectionHorizontal() const
{
	float horizontal = 0.0f;
	if(rightFlag)
	{
		horizontal += 1;
	}

	if (leftFlag)
	{
		horizontal -= 1;
	}
	return horizontal;
}

float Input::GetKeyboardDirectionVertical() const
{
	float vertical = 0.0f;
	if (upFlag)
	{
		vertical += 1;
	}

	if (downFlag)
	{
		vertical -= 1;
	}
	return vertical;
}

void Input::SetMousePosition(int x, int y)
{
	this -> x = x;
	this->y = y;
}

void Input::GetHitOnXZ(const Camera& camera, Vector3& hitPos) const
{
	Vector3 rayOrigin = camera.ScreenPosTo3DPos(x, y, 0.0f);
	Vector3 rayTarget = camera.ScreenPosTo3DPos(x, y, 1.0f);
	Vector3 rayDirection = (rayTarget - rayOrigin).Normalized();

	bool hit = RaycastPlane(rayOrigin, rayDirection, Vector3(), Vector3(0,1,0), hitPos);
}
