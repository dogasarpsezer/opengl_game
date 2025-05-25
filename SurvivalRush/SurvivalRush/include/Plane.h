#pragma once

inline bool RaycastPlane(const Vector3& rayOrigin, const Vector3& rayDir,
    const Vector3& planePoint, const Vector3& planeNormal,
    Vector3& outHitPoint)
{
    float denom = planeNormal.Dot(rayDir);
    if (fabs(denom) < 0.0001f)
        return false;  // Ray is parallel to the plane, since the normal is always 90 to the plane

    float t = (planePoint - rayOrigin).Dot(planeNormal) / denom;
    if (t < 0)
        return false;  // Intersection is behind the ray origin

    outHitPoint = rayOrigin + rayDir * t;
    return true;
}
