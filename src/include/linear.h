//
// Created by edoardo on 7/22/25.
//

#ifndef LINEAR_H
#define LINEAR_H

#include <algorithm>
#include <cmath>

using std::cos;
using std::sin;


struct Vector3 {
    float x, y, z;

    Vector3 operator+(const Vector3 &v) const;

    Vector3 operator-(const Vector3 &v) const;

    [[nodiscard]] Vector3 cross(const Vector3 &v) const;

    [[nodiscard]] float dot(const Vector3 &v) const;

    [[nodiscard]] Vector3 normalize() const;

    [[nodiscard]] float module() const;
};

struct Reference {
    // Composition of 3 rotation linear transformation with respect to each axis
    [[nodiscard]] Vector3 rotatePoint(const Vector3 v) const;

    // Change axis orientation by euler angles in Euclidian space
    void rotateReference(const float alpha_, const float beta_, const float delta_);

private:
    float m_alpha = 0.f;
    float m_beta = 0.f;
    float m_delta = 0.f;

    float m_cosAlpha = cos(m_alpha);
    float m_cosBeta = cos(m_beta);
    float m_cosDelta = cos(m_delta);
    float m_sinAlpha = sin(m_alpha);
    float m_sinBeta = sin(m_beta);
    float m_sinDelta = sin(m_delta);
};


#endif //LINEAR_H
