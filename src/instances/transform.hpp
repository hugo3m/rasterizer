#pragma once

#include <memory>
#include "../math/vec.hpp"
#include "rotation.hpp"

using namespace std;

class Transform
{
private:
    Vec3 _translation;
    Rotation _rotation;
    Vec3 _scale;

public:
    Transform(Vec3 translation, Rotation rotation, Vec3 scale);

    Transform();

    Vec3 GetTranslation() const;
    Rotation GetRotation() const;
    Vec3 GetScale() const;

    void SetTranslation(Vec3 value);
};