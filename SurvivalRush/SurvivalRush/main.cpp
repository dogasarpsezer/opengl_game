#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Color.h"
#include "CustomText.h"
#include "EnemyManager.h"
#include "include/Player.h";
#include "include/Collectible.h";
#include "Camera.h"
#include "Debug.h"
#include "include/Weapon.h"
#include "CustomTime.h"
#include "include/Input.h";

Camera camera(10,3);
bool debugActive = true;
Input inputManager = Input();
Player playerCharacter(50,10,0.1f,1,10,Collider(0.5f));
float score = 0;
const float playerSpeed = 5.0f;
float bestScore;

void start()
{
    score = 0;
    BulletManager::Instance().Clear();
    CollectibleManager::Instance().Reset();
    playerCharacter.Reset();

    Vector3 pos = Vector3(0, 20, 0);
    camera.transform.SetPosition(pos); // 10 units above, looking down
    camera.transform.SetRotation(Vector3(-90, 0, 0)); // looking straight down

    camera.Init(60, 800.0 / 600.0, 0.1f, 100.0f);
    camera.offset = pos - playerCharacter.transform.position;


    CustomTime::Instance().Init(std::chrono::steady_clock::now());

    EnemyManager::Instance().spawnMinTime = 0.1f;
    EnemyManager::Instance().spawnNewEnemyTime = 3.0f;
    EnemyManager::Instance().timeDecreasePerSpawn = 0.05f;
    EnemyManager::Instance().Reset();
}

void init() {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // background
    glEnable(GL_DEPTH_TEST);

    start();
}

void restart()
{
    if (score > bestScore) bestScore = score;
    start();
}

void menuSelected(int value)
{
    switch (value)
    {
    case 0:
        debugActive = !debugActive;
        break;
    case 1:
        restart();
        break;
    default:
        break;
    }
}

void menu()
{
    int menuId = glutCreateMenu(menuSelected);
    glutAddMenuEntry("Toggle Debug", 0);
    glutAddMenuEntry("Restart", 1);
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

char* GetScoreText(float score)
{
    // Convert to minutes and seconds
    int minutes = static_cast<int>(score) / 60;
    int seconds = static_cast<int>(score) % 60;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Score: %02dm %02ds", minutes, seconds);

    return buffer;
}

char* GetHealthText(Player& player)
{
    // Convert to minutes and seconds
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Health: %.0f/%.0f", player.health, player.maxHealth);

    return buffer;
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
    playerCharacter.PlayerActionUpdate(inputManager);

    BulletManager::Instance().Update();
    EnemyManager::Instance().Update(playerCharacter);
    CollectibleManager::Instance().Update(playerCharacter);

    score += CustomTime::Instance().deltaTime;

    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);
    DrawText(GetScoreText(score), width, height, 30, height - 30,GLUT_BITMAP_HELVETICA_18);
    DrawText(GetScoreText(bestScore), width, height, 30, height - 45,GLUT_BITMAP_HELVETICA_12);
   
    int fontHeight = 18;
    int y = 30; // distance from bottom
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)GetHealthText(playerCharacter));
    int x = (width - textWidth) / 2;

    DrawText(GetHealthText(playerCharacter), width, height, x, y, GLUT_BITMAP_HELVETICA_18);
    if(debugActive) Debug::Instance().Update();

    glutSwapBuffers();

    if (playerCharacter.Dead())
    {
        restart();
    }
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
        inputManager.leftMouseDown = state == GLUT_DOWN;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Geometry Survival");

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


