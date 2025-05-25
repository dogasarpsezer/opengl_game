#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "include/SimpleGeo.h"
#include "Color.h"
#include "include/SimpleCharacter.h";
#include "Camera.h"
#include "Plane.h"
#include "Debug.h"
#include "CustomTime.h"
#include <iostream>
#include "include/Input.h";

Camera camera;
Debug debug;
bool debugActive = true;
Input inputManager = Input();
CustomTime customTime(std::chrono::steady_clock::now());

SimpleCharacter playerCharacter(TRIANGLE);

const float playerSpeed = 5.0f;

void init() {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // background
    glEnable(GL_DEPTH_TEST);

    camera.transform.SetPosition(Vector3(0, 20, 0)); // 10 units above, looking down
    camera.transform.SetRotation(Vector3(-90, 0, 0)); // looking straight down

    camera.Init(60, 800.0 / 600.0, 0.1f, 100.0f);


    playerCharacter.SetColor(green);
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


void update() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    debug.Cleanup();

    customTime.Update();

    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);

    //playerCharacter.transform.RotateOnY(angleToRotate);

#pragma region Keyboard Input Handle 
    
    float horizontalInput = inputManager.GetKeyboardDirectionHorizontal();
    float verticalInput = inputManager.GetKeyboardDirectionVertical();

    Vector3 forwardInput = playerCharacter.transform.Forward() * verticalInput;
    Vector3 rightInput = playerCharacter.transform.Right() * horizontalInput;

    Vector3 dir = (forwardInput + rightInput).Normalized();

    Vector3 movement = dir * (playerSpeed * customTime.deltaTime);
    Vector3 cameraNewPos = camera.transform.position + movement;
#pragma endregion

    //camera.transform.SetPosition(cameraNewPos);
    camera.Update();

    Vector3 hitPos;
    inputManager.GetHitOnXZ(camera, hitPos);

    Vector3 playerDir = (hitPos - playerCharacter.transform.position).Normalized();
    float angleToRotate = SignedAngleBetween(playerCharacter.transform.Forward(), playerDir, up);

    float maxTurnPerFrame = 180.0f * customTime.deltaTime * 10; // degrees per second
    angleToRotate = Clamp(angleToRotate, -maxTurnPerFrame, maxTurnPerFrame);

    playerCharacter.transform.RotateOnY(angleToRotate);

    playerCharacter.transform.Move(movement);
    playerCharacter.Update();


    SimpleCharacter* inputDebug = new SimpleCharacter(SimpleGeo(CIRCLE,white));
    SimpleCharacter* playerForwardDebug = new SimpleCharacter(SimpleGeo(SQUARE,blue));
    SimpleCharacter* playerRightDebug = new SimpleCharacter(SimpleGeo(SQUARE,red));

    playerForwardDebug->transform.SetPosition(playerCharacter.transform.position + playerCharacter.transform.Forward() * 3);
    playerRightDebug->transform.SetPosition(playerCharacter.transform.position + playerCharacter.transform.Right() * 3);
    inputDebug->transform.SetPosition(hitPos);

    debug.AddDebug(inputDebug);
    debug.AddDebug(playerForwardDebug);
    debug.AddDebug(playerRightDebug);

    if(debugActive) debug.Update();

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

void passiveMouse(int x,int y)
{
    inputManager.SetMousePosition(x,y);
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
    glutPassiveMotionFunc(passiveMouse);

    menu();
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
}


