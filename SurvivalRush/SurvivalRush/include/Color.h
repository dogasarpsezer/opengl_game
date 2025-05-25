#pragma once

#include <windows.h>    // required before gl.h on Windows
#include <gl/GL.h>
#include <gl/GLU.h>

class Color
{
public:
	Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
private:
	
};

inline Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a) {}

extern const Color red;
extern const Color blue;
extern const Color green;
extern const Color yellow;
extern const Color cyan;
extern const Color magenta;
extern const Color orange;
extern const Color purple;
extern const Color white;
extern const Color black;
