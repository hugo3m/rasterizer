#include "triangle.hpp"

Triangle::Triangle(shared_ptr<Vec3> v1, shared_ptr<Vec3> v2, shared_ptr<Vec3> v3) : _vertices({v1, v2, v3})
{
}

array<shared_ptr<Vec3>, 3> Triangle::GetVertices() const
{
    return this->_vertices;
}

bool Triangle::IsFacing(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &cameraPosition)
{
    Vec3 d1 = v2 - v1;
    Vec3 d2 = v3 - v1;
    Vec3 direction = v1 - cameraPosition;
    Vec3 normal = d1.CrossProduct(d2);
    return normal.Dot(direction) > 0;
}