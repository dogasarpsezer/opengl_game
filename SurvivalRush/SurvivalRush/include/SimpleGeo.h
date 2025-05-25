#pragma once
#include "Vector.h"
#include "Transform.h"
#include "Color.h"
#include <windows.h>    // required before gl.h on Windows
#include <GL/gl.h>
#include <GL/glu.h>

enum GeoType
{
	TRIANGLE,
	CIRCLE,
	SQUARE
};

class SimpleGeo {
public:
	SimpleGeo(GeoType geoType,Color color = white,float size = 1.0f);
	void Draw(Transform transform);
	Color color;
private:
	GeoType geoType;
	float size;
};
