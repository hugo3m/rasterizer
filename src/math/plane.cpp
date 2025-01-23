#include "plane.hpp"

Plane::Plane(Vec3 normal, double d) : _normal(normal), _d(d)
{
    double norm = this->_normal.Norm();
    if (norm == 1)
        return;
    this->_normal = this->_normal / norm;
    this->_d = this->_d / norm;
};

Plane::Plane(Vec3 normal, Vec3 point) : Plane(normal, normal.Dot(point))
{
}

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

bool Plane::HasIntersection(const Vec3 &direction) const
{
    const double dot = direction.Dot(this->_normal);
    return dot != 0;
};

Vec3 Plane::Intersection(const Vec3 &origin, const Vec3 &direction) const
{
    const double coefficient = (-this->_d - this->_normal.Dot(origin)) / this->_normal.Dot(direction);
    return origin + (direction * coefficient);
}