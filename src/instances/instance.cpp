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

Matrix Instance::GenerateMatrixInstance() const
{
    Vec3 translation = this->_transform.GetTranslation();
    Vec3 scale = this->_transform.GetScale();
    Matrix matrixTranslation = Matrix({1, 0, 0, translation.x, 0, 1, 0, translation.y, 0, 0, 1, translation.z, 0, 0, 0, 1}, 4, 4);
    Matrix matrixScale = Matrix({scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1}, 4, 4);
    return matrixTranslation * matrixScale * this->_transform.GetRotation().GenerateMatrixRotation();
}