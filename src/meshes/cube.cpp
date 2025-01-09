#include "cube.hpp"

CubeModel::CubeModel(shared_ptr<Triangle> t1,
                     shared_ptr<Triangle> t2,
                     shared_ptr<Triangle> t3,
                     shared_ptr<Triangle> t4,
                     shared_ptr<Triangle> t5,
                     shared_ptr<Triangle> t6,
                     shared_ptr<Triangle> t7,
                     shared_ptr<Triangle> t8,
                     shared_ptr<Triangle> t9,
                     shared_ptr<Triangle> t10,
                     shared_ptr<Triangle> t11,
                     shared_ptr<Triangle> t12) : _triangles({t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12}) {};

vector<shared_ptr<Triangle>> CubeModel::GetTriangles() const
{

    return vector<shared_ptr<Triangle>>(begin(this->_triangles), end(this->_triangles));
}

vector<shared_ptr<Vec3>> CubeModel::GetUniqueVertices() const
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