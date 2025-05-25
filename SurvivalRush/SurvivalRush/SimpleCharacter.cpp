#include "include/SimpleCharacter.h";

SimpleCharacter::SimpleCharacter(SimpleGeo geometryShape) : geometry(geometryShape), transform() {}


void SimpleCharacter::Update()
{
	geometry.Draw(transform);
}

void SimpleCharacter::SetColor(Color color)
{
	geometry.color = color;
}