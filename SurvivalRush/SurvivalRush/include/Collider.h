#pragma once
#include "Vector.h"
#include "SimpleCharacter.h"
#include "Color.h"
#include "Debug.h"

class Collider
{
public:
	Collider(float radius) : radius(radius) {}

	float GetRadius(float scale)
	{
		return radius * scale;
	}

	void DrawDebug(Vector3 center, Vector3 scale)
	{
		SimpleCharacter* colliderDebug = new SimpleCharacter(SimpleGeo(CIRCLE_BOUNDS, cyan, 1.0f));
		colliderDebug->transform.SetPosition(center);
		colliderDebug->transform.SetScale(scale * (radius * 2));

		Debug::Instance().AddDebug(colliderDebug);
	}

private:
	float radius;
};

inline bool CircleCollision(Vector3& p1, float& r1, Vector3& p2, float& r2)
{
	//sqr length is much faster
	float pointDistance = (p1 - p2).SqrLength();
	float minDistanceForCollision = r1 + r2;

	return pointDistance < minDistanceForCollision * minDistanceForCollision;
}
