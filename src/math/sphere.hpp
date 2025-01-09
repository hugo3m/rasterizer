#pragma once

#include "vec.hpp"

class Sphere
{
private:
    Vec3 _center;
    double _radius;

public:
    Sphere(Vec3 center, double radius);

    Vec3 GetCenter() const;

    double GetRadius() const;
};