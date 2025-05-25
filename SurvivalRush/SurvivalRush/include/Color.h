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

const Color red(1.0f, 0.0f, 0.0f);
const Color blue(0.0f, 0.0f, 1.0f);
const Color green(0.0f, 1.0f, 0.0f);
const Color yellow(1.0f, 1.0f, 0.0f);    // bright yellow
const Color cyan(0.0f, 1.0f, 1.0f);      // teal/light blue
const Color magenta(1.0f, 0.0f, 1.0f);   // pinkish purple
const Color orange(1.0f, 0.5f, 0.0f);    // orange
const Color purple(0.5f, 0.0f, 0.5f); // deep purple 
const Color white(1.0f, 1.0f, 1.0f);
const Color black(0.0f, 0.0f, 0.0f);
