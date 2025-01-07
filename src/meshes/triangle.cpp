#include "triangle.hpp"

TriangleModel::TriangleModel(shared_ptr<Triangle> t) : _triangle(t)
{
}

vector<shared_ptr<Triangle>> TriangleModel::GetTriangles() const
{
    vector<shared_ptr<Triangle>> res;
    res.push_back(this->_triangle);
    return res;
}