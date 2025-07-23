//
// Created by edoardo on 7/23/25.
//

#include "linear.h"

Vector3 Vector3::operator+(const Vector3& v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return {x - v.x, y - v.y, z - v.z};
}

[[nodiscard]] Vector3 Vector3::cross(const Vector3& v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}
[[nodiscard]] float Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

[[nodiscard]] Vector3 Vector3::normalize() const {
    const float len = module();
    return {x / len, y / len, z / len};
}

[[nodiscard]] float Vector3::module() const {
    return std::sqrt(x * x + y * y + z * z);
}

[[nodiscard]] Vector3 Reference::rotatePoint(const Vector3 v) const {
    const float x =  v.x;
    const float y =  v.y;
    const float z =  v.z;
    const float newX = x*cosAlpha*cosBeta + y*(cosAlpha*sinBeta*sinDelta - sinAlpha*cosDelta) + z*(cosAlpha*sinBeta*cosDelta + sinAlpha*sinDelta);
    const float newY = x*sinAlpha*cosBeta + y*(sinAlpha*sinBeta*sinDelta + cosAlpha*cosDelta) + z*(sinAlpha*sinBeta*cosDelta - cosAlpha*sinDelta);
    const float newZ = -x*sinBeta + y*cosBeta*sinDelta + z*cosBeta*cosDelta;
    return Vector3{newX,newY,newZ};
}

void Reference::rotateReference(const float alpha_, const float beta_, const float delta_)  {
    alpha +=  alpha_;
    beta +=  beta_;
    delta +=  delta_;
    cosAlpha = cos(alpha);
    cosBeta = cos(beta);
    cosDelta = cos(delta);
    sinAlpha = sin(alpha);
    sinBeta = sin(beta);
    sinDelta = sin(delta);
}
