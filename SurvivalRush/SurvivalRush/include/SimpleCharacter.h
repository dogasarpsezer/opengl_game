#pragma once

#include "include/Transform.h";
#include "include/SimpleGeo.h";

class SimpleCharacter
{
public:
	SimpleCharacter(SimpleGeo geometryShape);
	Transform transform;
	void Update();
	void SetColor(Color color);
private:
	SimpleGeo geometry;
};