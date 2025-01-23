#pragma once

#include "vec.hpp"

class Plane
{
private:
    // _normal.x * x + _normal.y * y + _normal.z * z = d
    Vec3 _normal;
    double _d;

public:
    Plane(Vec3 normal, double d);

    Plane(Vec3 normal, Vec3 point);

    Vec3 GetNormal() const;

    double GetD() const;

    double SignedDist(const Vec3 &point) const;

    bool IsInFront(const Vec3 &point) const;

    bool IsIn(const Vec3 &point) const;

    bool HasIntersection(const Vec3 &direction) const;

    Vec3 Intersection(const Vec3 &origin, const Vec3 &direction) const;
};