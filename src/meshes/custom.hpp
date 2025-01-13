
#pragma once

#include <memory>
#include "../math/triangle.hpp"
#include "mesh.hpp"

class CustomMesh : public Mesh
{
private:
    vector<shared_ptr<Triangle>> _triangles;

public:
    CustomMesh(vector<shared_ptr<Triangle>> triangles);

    vector<shared_ptr<Triangle>> GetTriangles() const;

    vector<shared_ptr<Vec3>> GetUniqueVertices() const;
};