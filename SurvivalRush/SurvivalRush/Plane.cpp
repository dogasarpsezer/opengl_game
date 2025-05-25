#include "include/Plane.h"
#include "include/Vector.h"
#include <GL/gl.h>
#include <GL/glu.h>
// Plane.cpp

Plane::Plane(float size, Vector3 normal)
    : halfSize(size / 2.0f), normal(normal) // even cleaner
{
}

void Plane::Draw() const {
    glColor3f(0.6f, 0.8f, 0.6f); // greenish
    glBegin(GL_QUADS);
    glVertex3f(-halfSize, 0.0f, -halfSize);
    glVertex3f(halfSize, 0.0f, -halfSize);
    glVertex3f(halfSize, 0.0f, halfSize);
    glVertex3f(-halfSize, 0.0f, halfSize);
    glEnd();
}