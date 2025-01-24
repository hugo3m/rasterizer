#include "material.hpp"

Material::Material(RGBA color, double specular, double reflective) : _color(color), _specular(specular), _reflective(reflective) {};

RGBA Material::GetColor() const
{
    return this->_color;
};

double Material::GetSpecular() const
{
    return this->_specular;
};

double Material::GetReflective() const
{
    return this->_reflective;
};