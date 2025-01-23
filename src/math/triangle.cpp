#include "triangle.hpp"
#include "plane.hpp"

Triangle::Triangle(const shared_ptr<Vec3> v1, const shared_ptr<Vec3> v2, const shared_ptr<Vec3> v3) : _vertices({v1, v2, v3})
{
}
Triangle::Triangle(const Triangle &triangle) : _vertices(triangle.GetVertices())
{
}

array<shared_ptr<Vec3>, 3> Triangle::GetVertices() const
{
    return this->_vertices;
}

Vec3 Triangle::GetNormal() const
{
    Vec3 d1 = *this->_vertices[1] - *this->_vertices[0];
    Vec3 d2 = *this->_vertices[2] - *this->_vertices[0];
    return d1.CrossProduct(d2);
}

bool Triangle::IsFacing(const Vec3 &origin) const
{
    Vec3 direction = *this->_vertices[0] - origin;
    return this->GetNormal().Dot(direction) > 0;
}

Triangle Triangle::Matrixed(const Matrix &matrixCamera, const Matrix &matrixInstance) const
{
    Matrix matrixFactor = matrixCamera * matrixInstance;
    // multiply each vertices
    unique_ptr<Vec> v1Factored = matrixFactor * VecHomogenous(this->_vertices[0]->x, this->_vertices[0]->y, this->_vertices[0]->z, 1);
    unique_ptr<Vec> v2Factored = matrixFactor * VecHomogenous(this->_vertices[1]->x, this->_vertices[1]->y, this->_vertices[1]->z, 1);
    unique_ptr<Vec> v3Factored = matrixFactor * VecHomogenous(this->_vertices[2]->x, this->_vertices[2]->y, this->_vertices[2]->z, 1);
    // cast to vec3
    Vec3 *v1 = dynamic_cast<Vec3 *>(v1Factored.get());
    Vec3 *v2 = dynamic_cast<Vec3 *>(v2Factored.get());
    Vec3 *v3 = dynamic_cast<Vec3 *>(v3Factored.get());
    return Triangle(make_shared<Vec3>(*v1), make_shared<Vec3>(*v2), make_shared<Vec3>(*v3));
}

bool Triangle::HasIntersection(const Vec3 &origin, const Vec3 &direction) const
{
    Plane layingPlane = Plane(this->GetNormal(), *this->_vertices[0]);
    if (!layingPlane.HasIntersection(direction))
    {
        return false;
    }
    Vec3 intersection = layingPlane.Intersection(origin, direction);
    for (int i = 0; i < this->_vertices.size(); i++)
    {
        Vec3 source = *this->_vertices[i];
        Vec3 edge = *this->_vertices[i % this->_vertices.size()] - source;
        Vec3 sourceToIntersection = intersection - source;
        if (edge.Dot(sourceToIntersection) <= 0)
        {
            return false;
        }
    }
    return true;
}