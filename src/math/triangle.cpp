#include "triangle.hpp"

Triangle::Triangle(shared_ptr<Vec3> v1, shared_ptr<Vec3> v2, shared_ptr<Vec3> v3) : _vertices({v1, v2, v3})
{
}

array<shared_ptr<Vec3>, 3> Triangle::GetVertices() const
{
    return this->_vertices;
}