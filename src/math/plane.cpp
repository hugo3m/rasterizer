#include "plane.hpp"

Plane::Plane(Vec3 normal, double d) : _normal(normal), _d(d)
{
    double norm = this->_normal.Norm();
    if (norm == 1)
        return;
    this->_normal = this->_normal / norm;
    this->_d = this->_d / norm;
};

Vec3 Plane::GetNormal() const
{
    return this->_normal;
};

double Plane::GetD() const
{
    return this->_d;
};

bool Plane::IsInFront(const Vec3 &point) const
{
    return point.Dot(this->_normal) > this->_d;
};
