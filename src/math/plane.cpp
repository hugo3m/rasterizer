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
    return this->SignedDist(point) > 0;
};

double Plane::SignedDist(const Vec3 &point) const
{
    return this->_normal.Dot(point) - this->_d;
};

bool Plane::IsIn(const Vec3 &point) const
{
    return this->SignedDist(point) == 0;
};

bool Plane::HasIntersection(const Vec3 &from, const Vec3 &to) const
{
    const Vec3 fromTo = to - from;
    const double dot = fromTo.Dot(this->_normal);
    return dot != 0;
};

Vec3 Plane::Intersection(const Vec3 &from, const Vec3 &to) const
{
    const Vec3 fromTo = to - from;
    const double coefficient = (-this->_d - this->_normal.Dot(from)) / this->_normal.Dot(fromTo);
    return from + (fromTo * coefficient);
}