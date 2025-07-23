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
    float x,y,z;

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;

    [[nodiscard]] Vector3 cross(const Vector3& v) const;
    [[nodiscard]] float dot(const Vector3& v) const;
    [[nodiscard]] Vector3 normalize() const;
    [[nodiscard]] float module() const;
};

// Light direction
const Vector3 lightDir = Vector3{0, 1, -1}.normalize();

struct Reference {
    // Composition of 3 rotation linear transformation with respect to each axis
    [[nodiscard]] Vector3 rotatePoint(const Vector3 v) const;
    // Change axis orientation by euler angles in Euclidian space
    void rotateReference(const float alpha_, const float beta_, const float delta_);
private:
    float alpha = 0.f;
    float beta = 0.f;
    float delta = 0.f;

    float cosAlpha = cos(alpha);
    float cosBeta = cos(beta);
    float cosDelta = cos(delta);
    float sinAlpha = sin(alpha);
    float sinBeta = sin(beta);
    float sinDelta = sin(delta);
};





#endif //LINEAR_H
