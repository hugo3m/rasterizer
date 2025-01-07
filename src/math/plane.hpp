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

    double SignedDist(const Vec3 &point) const;

    bool IsInFront(const Vec3 &point) const;

    bool IsIn(const Vec3 &point) const;

    bool HasIntersection(const Vec3 &from, const Vec3 &to) const;

    Vec3 Intersection(const Vec3 &from, const Vec3 &to) const;
};