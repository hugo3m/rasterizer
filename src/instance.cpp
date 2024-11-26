#include "instance.hpp"

Instance::Instance(shared_ptr<Model> model, Vec3 position) : _model(model), _position(position) {};

shared_ptr<Model> Instance::GetModel() const
{
    return this->_model;
};

Vec3 Instance::GetPosition() const
{
    return this->_position;
};