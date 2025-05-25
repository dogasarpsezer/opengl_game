#pragma once
#include <vector>
#include "SimpleCharacter.h"

class Debug
{
public:
	void Update();
	void Cleanup();
	void AddDebug(SimpleCharacter* debugItem);
private:
	//List Simple Character
	std::vector<SimpleCharacter*> debugItems;
};