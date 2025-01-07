#include "instance.hpp"

Instance::Instance(shared_ptr<Model> model, Transform transform) : _model(model), _transform(transform) {};

shared_ptr<Model> Instance::GetModel() const
{
    return this->_model;
};

Transform Instance::GetTransform() const
{
    return this->_transform;
};