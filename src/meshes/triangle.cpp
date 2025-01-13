#include "triangle.hpp"

TriangleMesh::TriangleMesh(shared_ptr<Triangle> t) : _triangle(t)
{
}

vector<shared_ptr<Triangle>> TriangleMesh::GetTriangles() const
{
    vector<shared_ptr<Triangle>> res;
    res.push_back(this->_triangle);
    return res;
}

vector<shared_ptr<Vec3>> TriangleMesh::GetUniqueVertices() const
{
    vector<shared_ptr<Vec3>> res;
    for (const auto vertice : this->_triangle->GetVertices())
    {
        bool isIn = false;
        for (const auto addedVertice : res)
        {
            if ((*addedVertice) == (*vertice))
            {
                isIn = true;
            }
        }
        if (!isIn)
        {
            res.push_back(vertice);
        }
    }
    return res;
}
