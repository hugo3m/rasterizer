#include "sphere.hpp"

Sphere::Sphere(Vec3 center, double radius) : _center(center), _radius(radius) {};

Vec3 Sphere::GetCenter() const
{
    return this->_center;
};

double Sphere::GetRadius() const
{
    return this->_radius;
};