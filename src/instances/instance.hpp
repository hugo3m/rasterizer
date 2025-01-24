#pragma once

#include <memory>
#include "../meshes/mesh.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"
#include "../render/material.hpp"
#include "transform.hpp"

using namespace std;

class Instance
{
private:
    shared_ptr<Mesh> _mesh;

    Transform _transform;

    shared_ptr<Material> _material;

public:
    Instance(shared_ptr<Mesh> mesh, Transform transform, shared_ptr<Material> material);

    shared_ptr<Mesh> GetMesh() const;

    Transform GetTransform() const;

    shared_ptr<Material> GetMaterial() const;

    Matrix GenerateMatrixInstance() const;

    Sphere GetBoundingSphere() const;
};