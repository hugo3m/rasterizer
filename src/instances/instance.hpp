#pragma once

#include <memory>
#include "../meshes/mesh.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"
#include "transform.hpp"

using namespace std;

class Instance
{
private:
    shared_ptr<Mesh> _mesh;
    Transform _transform;

public:
    Instance(shared_ptr<Mesh> mesh, Transform transform);

    shared_ptr<Mesh> GetMesh() const;

    Transform GetTransform() const;

    Matrix GenerateMatrixInstance() const;

    Sphere GetBoundingSphere() const;
};