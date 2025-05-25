#include "include/Debug.h"

Debug& Debug::Instance()
{
	static Debug instance; // only created once
	return instance;
}

void Debug::Cleanup()
{
	for (SimpleCharacter* c : debugItems)
		delete c;
	debugItems.clear();
}

void Debug::AddDebug(SimpleCharacter* debugItem) 
{
	debugItems.push_back(debugItem);
}

void Debug::Update()
{
	for (SimpleCharacter* c : debugItems)
	{
		c->Update();
	}
}