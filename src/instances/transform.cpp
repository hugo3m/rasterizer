#include "transform.hpp"

Transform::Transform(Vec3 translation, Rotation rotation, Vec3 scale) : _translation(translation), _rotation(rotation), _scale(scale) {};
Vec3 Transform::GetTranslation() const
{
    return this->_translation;
};
Rotation Transform::GetRotation() const
{
    return this->_rotation;
};
Vec3 Transform::GetScale() const
{
    return this->_scale;
};
void Transform::SetTranslation(Vec3 value)
{
    this->_translation = value;
};
Transform::Transform() : _translation(Vec3(0, 0, 0)), _rotation(Rotation(0, 0, 0)), _scale(Vec3(0, 0, 0)) {};

void Transform::SetRotation(Rotation value)
{
    this->_rotation = value;
}