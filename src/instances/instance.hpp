#pragma once

#include <memory>
#include <functional>

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

    vector<function<void(Instance &, const double deltaTime)>> _updateBehaviors;

public:
    Instance(shared_ptr<Mesh> mesh, Transform transform, shared_ptr<Material> material);

    shared_ptr<Mesh> GetMesh() const;

    Transform GetTransform() const;

    shared_ptr<Material> GetMaterial() const;

    Matrix GenerateMatrixInstance() const;

    vector<shared_ptr<Triangle>> GetSceneTriangles(const Matrix &matrixCamera) const;

    vector<shared_ptr<Triangle>> GetRawTriangles() const;

    Sphere GetBoundingSphere() const;

    void AddUpdateBehavior(function<void(Instance &, const double deltaTime)> updateBehavior);

    void Update(const double deltaTime);

    void SetTransform(Transform value);
};