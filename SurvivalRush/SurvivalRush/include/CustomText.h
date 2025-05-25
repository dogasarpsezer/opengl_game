#pragma once
#include <cstdio>
#include <windows.h>    // required before gl.h on Windows
#include <gl/GL.h>
#include <gl/GLU.h>

void RenderBitmapString(float x, float y, void* font, const char* string) {
    glRasterPos2f(x, y); // Set the position to draw text
    while (*string) {
        glutBitmapCharacter(font, *string); // Draw each char
        ++string;
    }
}

void DrawText(const char text[], int windowWidth, int windowHeight, float x, float y,void* font) {
    // Turn int into string

    // ----- Switch to orthographic 2D projection -----
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();         
    glLoadIdentity();        
    gluOrtho2D(0, windowWidth, 0, windowHeight); // Define screen-space coords

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();          
    glLoadIdentity();       

    // ----- Draw the text -----
    glColor3f(1, 1, 1); // Set text color to white
    RenderBitmapString(x, y, font, text);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
