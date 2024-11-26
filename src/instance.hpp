#pragma once

#include <memory>
#include "models/model.hpp"
#include "math/vec.hpp"

using namespace std;

class Instance
{
private:
    shared_ptr<Model> _model;
    Vec3 _position;

public:
    Instance(shared_ptr<Model> model, Vec3 position);
    shared_ptr<Model> GetModel() const;
    Vec3 GetPosition() const;
};