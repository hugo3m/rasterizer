#pragma once

#include <array>
#include <memory>
#include "mesh.hpp"
#include "../math/vec.hpp"
#include "../math/triangle.hpp"

using namespace std;

class TriangleMesh : public Mesh
{
private:
    shared_ptr<Triangle> _triangle;

public:
    TriangleMesh(shared_ptr<Triangle> t);

    vector<shared_ptr<Triangle>> GetTriangles() const override;

    vector<shared_ptr<Vec3>> GetUniqueVertices() const override;
};