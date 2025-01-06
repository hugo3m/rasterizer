#pragma once

#include "vec.hpp"

class Plane
{
private:
    Vec3 _normal;
    double _d;

public:
    Plane(Vec3 normal, double d);

    Vec3 GetNormal() const;

    double GetD() const;

    bool IsInFront(const Vec3 &point) const;
};