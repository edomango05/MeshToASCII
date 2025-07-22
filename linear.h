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

    Vector3 operator+(const Vector3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    [[nodiscard]] Vector3 cross(const Vector3& v) const {
        return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        };
    }

    [[nodiscard]] float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    [[nodiscard]] Vector3 normalize() const {
        const float len = std::sqrt(x * x + y * y + z * z);
        return {x / len, y / len, z / len};
    }
};

// Light direction
const Vector3 lightDir = Vector3{0, 1, -1}.normalize();

struct Reference {

    // Composition of 3 rotation linear transformation with respect to each axis
    [[nodiscard]] Vector3 rotatePoint(const Vector3 v) const {
        const float x =  v.x;
        const float y =  v.y;
        const float z =  v.z;
        const float newX = x*cosAlpha*cosBeta + y*(cosAlpha*sinBeta*sinDelta - sinAlpha*cosDelta) + z*(cosAlpha*sinBeta*cosDelta + sinAlpha*sinDelta);
        const float newY = x*sinAlpha*cosBeta + y*(sinAlpha*sinBeta*sinDelta + cosAlpha*cosDelta) + z*(sinAlpha*sinBeta*cosDelta - cosAlpha*sinDelta);
        const float newZ = -x*sinBeta + y*cosBeta*sinDelta + z*cosBeta*cosDelta;
        return Vector3{newX,newY,newZ};
    }



    // Change axis orientation by euler angles in Euclidian space
    void rotateReference(const float alpha_, const float beta_, const float delta_)  {
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
