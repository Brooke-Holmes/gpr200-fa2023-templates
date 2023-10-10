#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include <cmath>

namespace bh {
    //Identity matrix
    inline ew::Mat4 Identity() {
        return ew::Mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    };

    //Scale on x,y,z axes
    inline ew::Mat4 Scale(ew::Vec3 s) {
        return ew::Mat4(
            s.x, 0, 0, 0,
            0, s.y, 0, 0,
            0, 0, s.z, 0,
            0, 0, 0, 1
        );
    };

    //Rotation around X axis (pitch) in radians
    inline ew::Mat4 RotateX(float rad) {
        float cosTheta = std::cos(rad);
        float sinTheta = std::sin(rad);
        return ew::Mat4(
            1, 0, 0, 0,
            0, cosTheta, -sinTheta, 0,
            0, sinTheta, cosTheta, 0,
            0, 0, 0, 1
        );
    };

    //Rotation around Y axis (yaw) in radians
    inline ew::Mat4 RotateY(float rad) {
        float cosTheta = std::cos(rad);
        float sinTheta = std::sin(rad);
        return ew::Mat4(
            cosTheta, 0, sinTheta, 0,
            0, 1, 0, 0,
            -sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1
        );
    };

    //Rotation around Z axis (roll) in radians
    inline ew::Mat4 RotateZ(float rad) {
        float cosTheta = std::cos(rad);
        float sinTheta = std::sin(rad);
        return ew::Mat4(
            cosTheta, -sinTheta, 0, 0,
            sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    };

    //Translate x,y,z
    inline ew::Mat4 Translate(ew::Vec3 t) {
        return ew::Mat4(
            1, 0, 0, t.x,
            0, 1, 0, t.y,
            0, 0, 1, t.z,
            0, 0, 0, 1
        );
    };
}

struct Transform {
    ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);
    ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f); // Euler angles (degrees)
    ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);

    ew::Mat4 getModelMatrix() const {
        ew::Mat4 translationMatrix = bh::Translate(position);
        ew::Mat4 rotationMatrix =
            bh::RotateY(rotation.y * (3.14159f / 180.0f)) *
            bh::RotateX(rotation.x * (3.14159f / 180.0f)) *
            bh::RotateZ(rotation.z * (3.14159f / 180.0f));
        ew::Mat4 scaleMatrix = bh::Scale(scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }
};
