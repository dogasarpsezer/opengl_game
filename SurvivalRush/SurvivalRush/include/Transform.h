#pragma once
#include "Vector.h"


class Transform
{
public:
    Transform(Vector3 position = Vector3(0, 0, 0),
        Vector3 rotation = Vector3(0, 0, 0),
        Vector3 scale = Vector3(1.0f, 1.0f, 1.0f));

    Vector3 Forward();
    Vector3 Right();

    void SetPosition(Vector3 newPosition);
    void SetRotation(Vector3 newRotation);
    void SetScale(Vector3 newScale);

    void Move(Vector3 movement);
    void RotateOnY(float angle);
    void UpdateMatrix(); // builds the model matrix
    GLfloat* ToGLMatrix();

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
private:


    GLfloat matrix[16]; // column-major, used in rendering
};

