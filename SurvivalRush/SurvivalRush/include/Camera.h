#pragma once
#include "Transform.h"
#include "Debug.h"
#include "CustomTime.h"
#include <windows.h>    // required before gl.h on Windows
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>


class Camera {
public:
	Camera(float followRadius,float normalizeSpeed);
	void Update(Vector3& playerPos);
    void Init(GLdouble fov, GLdouble aspect, GLdouble nearCam, GLdouble farCam);
    Vector3 ScreenPosTo3DPos(int x,int y) const;
    Vector3 ScreenPosTo3DPos(int x, int y, float depth) const;
	Transform transform;
    Vector3 offset;
private:
    float followRadius;
    float normalizeSpeed;
};

inline Camera::Camera(float followRadius,float normalizeSpeed) : transform(offset), followRadius(followRadius),normalizeSpeed(normalizeSpeed){}

inline void Camera::Init(GLdouble fov,GLdouble aspect,GLdouble nearCam, GLdouble farCam)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, nearCam, farCam);
    glMatrixMode(GL_MODELVIEW);
}

inline void Camera::Update(Vector3& playerPos) {

    float deltaTime = CustomTime::Instance().deltaTime;

    Vector3 followPos = transform.position - offset;
    SimpleCharacter* playerFollowRadiusDebug = new SimpleCharacter(SimpleGeo(CIRCLE, magenta));
    playerFollowRadiusDebug->transform.SetPosition(followPos + Vector3(0, -0.05f, 0));
    playerFollowRadiusDebug->transform.SetScale(Vector3(followRadius * 2, followRadius * 2, followRadius * 2));
    Debug::Instance().AddDebug(playerFollowRadiusDebug);

    Vector3 followDir = playerPos - followPos;
    float excessAmount = followDir.Length() - followRadius;
    bool isInFollowRadius = excessAmount <= 0.01f;

    std::cout << "Excess " << excessAmount << std::endl;

    if(isInFollowRadius == false)
    {
        Vector3 cameraMovementFollow = followDir.Normalized() * excessAmount;
        transform.Move(cameraMovementFollow);
    }



    Vector3 eye = transform.position;

    // Convert Euler angles to radians

    Vector3 target = eye + transform.Forward();
    Vector3 up(0, 1, 0); // global up (Y+)

    gluLookAt(
        eye.x, eye.y, eye.z,
        target.x, target.y, target.z,
        up.x, up.y, up.z
    );
}

inline Vector3 Camera::ScreenPosTo3DPos(int x, int y) const
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble worldX, worldY, worldZ;

    // Get matrices and viewport
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Flip Y: Windows has top-left origin, OpenGL uses bottom-left
    int winY = viewport[3] - y;

    float depth;
    // Read depth at mouse position (for more accurate result)
    glReadPixels(x, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    // Unproject screen (x, y, depth) to world coordinates
    gluUnProject(
        static_cast<GLdouble>(x),
        static_cast<GLdouble>(winY),
        static_cast<GLdouble>(depth),
        modelview, projection, viewport,
        &worldX, &worldY, &worldZ
    );

    return Vector3(static_cast<float>(worldX),
        static_cast<float>(worldY),
        static_cast<float>(worldZ));
}

inline Vector3 Camera::ScreenPosTo3DPos(int x, int y, float depth) const
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble worldX, worldY, worldZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    int winY = viewport[3] - y;

    gluUnProject(x, winY, depth, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    return Vector3((float)worldX, (float)worldY, (float)worldZ);
}

