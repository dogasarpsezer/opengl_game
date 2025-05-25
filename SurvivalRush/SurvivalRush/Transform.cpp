#include "include/Transform.h"

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 scl)
	: position(pos), rotation(rot), scale(scl)
{
	UpdateMatrix();
}

void Transform::SetPosition(Vector3 newPos) { position = newPos; UpdateMatrix(); }
void Transform::SetRotation(Vector3 newRot) { rotation = newRot; UpdateMatrix(); }
void Transform::SetScale(Vector3 newScale) { scale = newScale; UpdateMatrix(); }

void Transform::Move(Vector3 movement) { position = position + movement; UpdateMatrix(); }
void Transform::RotateOnY(float angle)
{
	rotation.y += angle;
	UpdateMatrix();
}

Vector3 Transform::Forward()
{
	float pitch = rotation.x * 3.14159f / 180.0f;
	float yaw = rotation.y * 3.14159f / 180.0f;

	Vector3 forward;
	forward.x = cos(pitch) * sin(yaw);
	forward.y = sin(pitch);
	forward.z = cos(pitch) * cos(yaw);

	return forward;
}

Vector3 Transform::Right()
{
	return Vector3(-matrix[0], -matrix[1], -matrix[2]).Normalized();
}

void Transform::UpdateMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);
	glScalef(scale.x, scale.y, scale.z);

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

GLfloat* Transform::ToGLMatrix()
{
	return matrix;
}

