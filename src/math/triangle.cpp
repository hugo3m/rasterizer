#include "triangle.hpp"
#include "plane.hpp"

#include <algorithm>

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
    Vec3 direction = origin - *this->_vertices[0];
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

Triangle Triangle::operator*(Matrix const &matrix) const
{
    // multiply each vertices
    unique_ptr<Vec> v0Factored = matrix * VecHomogenous(this->_vertices[0]->x, this->_vertices[0]->y, this->_vertices[0]->z, 1);
    unique_ptr<Vec> v1Factored = matrix * VecHomogenous(this->_vertices[1]->x, this->_vertices[1]->y, this->_vertices[1]->z, 1);
    unique_ptr<Vec> v2Factored = matrix * VecHomogenous(this->_vertices[2]->x, this->_vertices[2]->y, this->_vertices[2]->z, 1);

    vector<shared_ptr<Vec3>> res;

    for (const auto &vec : {v0Factored.get(), v1Factored.get(), v2Factored.get()})
    {
        if (VecHomogenous *castVec = dynamic_cast<VecHomogenous *>(vec))
        {
            res.push_back(make_shared<Vec3>(castVec->ToVec3()));
            continue;
        }
        if (Vec3 *castVec = dynamic_cast<Vec3 *>(vec))
        {
            res.push_back(make_shared<Vec3>(*castVec));
            continue;
        }
    }
    return Triangle(res[0], res[1], res[2]);
}

bool Triangle::HasIntersection(const Vec3 &origin, const Vec3 &direction) const
{
    Plane layingPlane = Plane(this->GetNormal(), *this->_vertices[0]);
    if (!layingPlane.HasIntersection(direction))
    {
        return false;
    }
    Vec3 intersection = layingPlane.Intersection(origin, direction);
    if ((intersection - origin).Dot(direction) < 0)
    {
        return false;
    }
    for (int i = 0; i < this->_vertices.size(); i++)
    {
        Vec3 source = *this->_vertices[i];
        Vec3 edge = *this->_vertices[(i + 1) % this->_vertices.size()] - source;
        Vec3 sourceToIntersection = intersection - source;
        if (edge.Dot(sourceToIntersection) <= 0)
        {
            return false;
        }
    }
    return true;
}

bool Triangle::operator==(const Triangle &other) const
{
    array<shared_ptr<Vec3>, 3> thisVertices = this->GetVertices();
    array<shared_ptr<Vec3>, 3> otherVertices = other.GetVertices();

    vector<int> thisCheckedIndexes;
    vector<int> otherCheckedIndexes;

    for (int thisIndex = 0; thisIndex < thisVertices.size(); thisIndex++)
    {
        shared_ptr<Vec3> thisVertice = thisVertices[thisIndex];
        bool isIn = false;
        for (int otherIndex = 0; otherIndex < otherVertices.size(); otherIndex++)
        {
            shared_ptr<Vec3> otherVertice = otherVertices[otherIndex];
            if (*thisVertice == *otherVertice && (find(thisCheckedIndexes.begin(), thisCheckedIndexes.end(), thisIndex) == thisCheckedIndexes.end()) && (find(otherCheckedIndexes.begin(), otherCheckedIndexes.end(), otherIndex) == otherCheckedIndexes.end()))
            {
                isIn = true;
                thisCheckedIndexes.push_back(thisIndex);
                otherCheckedIndexes.push_back(otherIndex);
            }
        }
        if (!isIn)
        {
            return false;
        }
    }
    return true;
}

void Triangle::Print() const
{
    printf("[(%f, %f, %f), (%f, %f, %f), (%f, %f, %f)] \n", this->_vertices[0]->x, this->_vertices[0]->y, this->_vertices[0]->z, this->_vertices[1]->x, this->_vertices[1]->y, this->_vertices[1]->z, this->_vertices[2]->x, this->_vertices[2]->y, this->_vertices[2]->z);
}