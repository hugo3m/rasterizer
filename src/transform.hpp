#pragma once

#include <memory>
#include "math/vec.hpp"

using namespace std;

class Transform
{
private:
    Vec3 _translation;
    double _rotation;
    double _scale;

public:
    Transform(Vec3 translation, double rotation, double scale);
    Vec3 GetTranslation() const;
    double GetRotation() const;
    double GetScale() const;
};