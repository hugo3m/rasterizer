#pragma once

#include "vec.hpp"

class Plane
{
private:
    Vec3 _normal;
    double _d;

public:
    Plane(Vec3 normal, double d);

    bool IsInFront(Vec3 point) const;
};