
#pragma once

#include <memory>
#include "../math/triangle.hpp"
#include "mesh.hpp"

class CubeMesh : public Mesh
{
private:
    array<shared_ptr<Triangle>, 12> _triangles;

public:
    CubeMesh(shared_ptr<Triangle> t1,
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
             shared_ptr<Triangle> t12);

    vector<shared_ptr<Triangle>> GetTriangles() const override;

    vector<shared_ptr<Vec3>> GetUniqueVertices() const override;
};