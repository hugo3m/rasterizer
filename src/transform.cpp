#include "transform.hpp"

Transform::Transform(Vec3 translation, double rotation, double scale) : _translation(translation), _rotation(rotation), _scale(scale) {};
Vec3 Transform::GetTranslation() const
{
    return this->_translation;
};
double Transform::GetRotation() const
{
    return this->_rotation;
};
double Transform::GetScale() const
{
    return this->_scale;
};