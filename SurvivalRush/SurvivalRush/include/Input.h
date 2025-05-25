#pragma once
#include "Vector.h";
#include "Camera.h";

class Input
{
public:
	Input();
	float GetKeyboardDirectionHorizontal();
	float GetKeyboardDirectionVertical();
	void GetKeyboardInputDown(unsigned char key);
	void GetKeyboardInputUp(unsigned char key);
	void SetMousePosition(int x,int y);
	void GetHitOnXZ(const Camera& camera,Vector3& hitPos);
	int x;
	int y;
private:
	const char up = 'w';
	const char down = 's';
	const char left = 'a';
	const char right = 'd';

	bool upFlag;
	bool downFlag;
	bool rightFlag;
	bool leftFlag;
};