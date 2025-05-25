#include "include/SimpleGeo.h";
#include <windows.h>    // required before gl.h on Windows
#include <gl/GL.h>
#include <gl/GLU.h>



SimpleGeo::SimpleGeo(GeoType geoType, Color color, float size)
	: geoType(geoType), color(color), size(size) {
}

void SimpleGeo::Draw(Transform transform)
{
	glPushMatrix();
	glMultMatrixf(transform.ToGLMatrix());
	float halfSize = size / 2.0f;
	glColor3f(color.r, color.g, color.b);
	switch (geoType)
	{
	case TRIANGLE:
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, halfSize);
		glVertex3f(-halfSize, 0.0f, -halfSize);
		glVertex3f(halfSize, 0.0f, -halfSize);
		glEnd();
		break;
	case CIRCLE:
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, 0);

		const int stepCount = 64;

		const float twoPI = 2 * 3.14159f;
		for (size_t i = 0; i <= stepCount; i++)
		{
			float t = static_cast<float>(i) / stepCount;
			float angle = t * twoPI;

			float x = cos(angle) * halfSize;
			float z = sin(angle) * halfSize;

			glVertex3f(x, 0, z);
		}
		glEnd();
		break;
	}
	case SQUARE:
		glBegin(GL_QUADS);
		glVertex3f(halfSize, 0.0f, halfSize);
		glVertex3f(halfSize, 0.0f, -halfSize);
		glVertex3f(-halfSize, 0.0f, -halfSize);
		glVertex3f(-halfSize, 0.0f, halfSize);
		glEnd();
		break;
	default:
		break;
	}


	glPopMatrix();
}