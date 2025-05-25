#pragma once
#include "Vector.h";
#include "Camera.h";

class Input
{
public:
	Input();
	float GetKeyboardDirectionHorizontal() const;
	float GetKeyboardDirectionVertical() const;
	void GetKeyboardInputDown(unsigned char key);
	void GetKeyboardInputUp(unsigned char key);
	void SetMousePosition(int x,int y);

	void GetHitOnXZ(const Camera& camera,Vector3& hitPos) const;
	int x;
	int y;

	int selectedSlot;
	bool leftMouseDown;
private:
	const char up = 'w';
	const char down = 's';
	const char left = 'a';
	const char right = 'd';

	const char selectedOne = '1';
	const char selectedTwo = '2';
	const char selectedThree = '3';
	
	bool upFlag;
	bool downFlag;
	bool rightFlag;
	bool leftFlag;
};