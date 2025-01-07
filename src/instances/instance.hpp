#pragma once

#include <memory>
#include "../meshes/model.hpp"
#include "../math/vec.hpp"
#include "transform.hpp"

using namespace std;

class Instance
{
private:
    shared_ptr<Model> _model;
    Transform _transform;

public:
    Instance(shared_ptr<Model> model, Transform transform);
    shared_ptr<Model> GetModel() const;
    Transform GetTransform() const;
};