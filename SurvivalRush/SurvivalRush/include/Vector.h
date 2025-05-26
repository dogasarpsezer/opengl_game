#pragma once
#include <cmath>
#include "CustomMath.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Vector3 {
public:
    GLfloat x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(GLfloat x_, GLfloat y_, GLfloat z_) : x(x_), y(y_), z(z_) {}
    // Operators
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Dot product
    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3 Cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    GLfloat SqrLength() const
    {
        return x * x + y * y + z * z;
    }

    // Magnitude
    GLfloat Length() const {
        return std::sqrt(SqrLength());
    }

    // Normalize
    Vector3 Normalized() const {
        float len = Length();
        return len > 0 ? *this / len : Vector3(0, 0, 0);
    }

    Vector3 ClampMagnitude(float maxLength) const
    {
        float len = Length();
        if (len > maxLength && len > 0.0001f)
        {
            return (*this / len) * maxLength;
        }
        return *this;
    }

    Vector3 RotateY(float degrees) {
        float radians = degrees * 3.14159f / 180.0f;
        float cosA = cos(radians);
        float sinA = sin(radians);

        return Vector3(
            x * cosA - z * sinA,
            y,
            x * sinA + z * cosA
        );
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }
};


inline float SignedAngleBetween(const Vector3& from, const Vector3& to, const Vector3& axis) {
    Vector3 axisNorm = axis.Normalized();

    // Project both vectors onto the plane perpendicular to the axis
    Vector3 fromProj = (from - axisNorm * from.Dot(axisNorm)).Normalized();
    Vector3 toProj = (to - axisNorm * to.Dot(axisNorm)).Normalized();

    // Compute angle using dot product
    float dot = Clamp(fromProj.Dot(toProj), -1.0f, 1.0f);
    float angle = acos(dot) * (180.0f / 3.14159f);  // degrees

    // Determine sign using cross product
    float sign = axisNorm.Dot(fromProj.Cross(toProj)) < 0 ? -1.0f : 1.0f;
    return angle * sign;
}

const Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
