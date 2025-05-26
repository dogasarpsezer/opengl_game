#include "include/Vector.h"

inline bool CircleCollision(Vector3& p1,float& r1,Vector3& p2, float& r2)
{
	//sqr length is much faster
	float pointDistance = (p1 - p2).SqrLength();
	float minDistanceForCollision = r1 + r2;

	return pointDistance < minDistanceForCollision * minDistanceForCollision;
}