#include "custom.hpp"

CustomMesh::CustomMesh(vector<shared_ptr<Triangle>> triangles) : _triangles(triangles) {};

vector<shared_ptr<Triangle>> CustomMesh::GetTriangles() const
{

    return this->_triangles;
}

vector<shared_ptr<Vec3>> CustomMesh::GetUniqueVertices() const
{
    vector<shared_ptr<Vec3>> res;
    for (const auto triangle : this->GetTriangles())
    {
        for (const auto vertice : triangle->GetVertices())
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
    }
    return res;
}