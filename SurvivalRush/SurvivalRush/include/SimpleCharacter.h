#pragma once
#include "Transform.h"
#include "SimpleGeo.h"

class SimpleCharacter
{
public:
	SimpleCharacter(SimpleGeo geometryShape);
	Transform transform;
	void Update();
	void SetColor(Color color);
protected:
	SimpleGeo geometry;
};