#pragma once

#include <memory>
#include "math/vec.hpp"

using namespace std;

class Transform
{
private:
    Vec3 _translation;
    double _rotation;
    Vec3 _scale;

public:
    Transform(Vec3 translation, double rotation, Vec3 scale);
    Vec3 GetTranslation() const;
    double GetRotation() const;
    Vec3 GetScale() const;
};