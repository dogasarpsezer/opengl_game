#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Color.h"
#include "include/Player.h";
#include "Camera.h"
#include "Debug.h"
#include "CustomTime.h"
#include <iostream>
#include "include/Input.h";

Camera camera(10,3);
bool debugActive = true;
Input inputManager = Input();
Player playerCharacter(10,0.1f,1,10);

const float playerSpeed = 5.0f;

void init() {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // background
    glEnable(GL_DEPTH_TEST);

    Vector3 pos = Vector3(0, 20, 0);
    camera.transform.SetPosition(pos); // 10 units above, looking down
    camera.transform.SetRotation(Vector3(-90, 0, 0)); // looking straight down

    camera.Init(60, 800.0 / 600.0, 0.1f, 100.0f);

    
    camera.offset = pos - playerCharacter.transform.position;

    playerCharacter.SetColor(green);

    CustomTime::Instance().Init(std::chrono::steady_clock::now());
}

void menuSelected(int value)
{
    switch (value)
    {
    case 0:
        debugActive = !debugActive;
        break;
    default:
        break;
    }
}

void menu()
{
    int menuId = glutCreateMenu(menuSelected);
    glutAddMenuEntry("Toggle Debug", 0);
}

void DrawGrid(float size = 50.0f, float step = 1.0f)
{
    glDisable(GL_LIGHTING); // optional, depends on your setup
    glColor3f(0.6f, 0.6f, 0.6f); // grid color (light gray)

    glBegin(GL_LINES);

    for (float i = -size; i <= size; i += step)
    {
        // Lines parallel to X
        glVertex3f(i, -1, -size);
        glVertex3f(i, -1, size);

        // Lines parallel to Z
        glVertex3f(-size, -1, i);
        glVertex3f(size, -1, i);
    }

    glEnd();
}

void update() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    Debug::Instance().Cleanup();

    CustomTime::Instance().Update();
    camera.Update(playerCharacter.transform.position);
    DrawGrid(50,10);
    playerCharacter.PlayerMotionUpdate(inputManager, camera);
    std::cout<<playerCharacter.transform.position.z<<std::endl;


    if(inputManager.leftMouseClicked) Debug::Instance().Update();

    glutSwapBuffers();
}

void keyboardDown(unsigned char key,int x, int y)
{
    inputManager.GetKeyboardInputDown(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
    inputManager.GetKeyboardInputUp(key);
}

void mouseMotion(int x,int y)
{
    inputManager.SetMousePosition(x,y);
}

void mouse(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        inputManager.leftMouseClicked = !inputManager.leftMouseClicked;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Top-Down Plane View");

    init();
    glutDisplayFunc(update);
    glutIdleFunc(update);
    
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);

    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouse);

    menu();
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
}


