//
// Created by edoardo on 7/23/25.
//

#include "linear.h"

Vector3 Vector3::operator+(const Vector3 &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector3 Vector3::operator-(const Vector3 &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

[[nodiscard]] Vector3 Vector3::cross(const Vector3 &v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}

[[nodiscard]] float Vector3::dot(const Vector3 &v) const {
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
    const float x = v.x;
    const float y = v.y;
    const float z = v.z;
    const float newX = x * m_cosAlpha * m_cosBeta + y * (m_cosAlpha * m_sinBeta * m_sinDelta - m_sinAlpha * m_cosDelta) + z * (
                           m_cosAlpha * m_sinBeta * m_cosDelta + m_sinAlpha * m_sinDelta);
    const float newY = x * m_sinAlpha * m_cosBeta + y * (m_sinAlpha * m_sinBeta * m_sinDelta + m_cosAlpha * m_cosDelta) + z * (
                           m_sinAlpha * m_sinBeta * m_cosDelta - m_cosAlpha * m_sinDelta);
    const float newZ = -x * m_sinBeta + y * m_cosBeta * m_sinDelta + z * m_cosBeta * m_cosDelta;
    return Vector3{newX, newY, newZ};
}

void Reference::rotateReference(const float alpha_, const float beta_, const float delta_) {
    m_alpha += alpha_;
    m_beta += beta_;
    m_delta += delta_;
    m_cosAlpha = cos(m_alpha);
    m_cosBeta = cos(m_beta);
    m_cosDelta = cos(m_delta);
    m_sinAlpha = sin(m_alpha);
    m_sinBeta = sin(m_beta);
    m_sinDelta = sin(m_delta);
}
