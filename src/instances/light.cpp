#include "light.hpp"

// **** Light ****
Light::Light(double intensity) : _intensity(intensity) {};

double Light::GetIntensity() const
{
    return this->_intensity;
}

// **** LightAmbient ****

LightAmbient::LightAmbient(double intensity) : Light(intensity) {};

double LightAmbient::Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const
{
    return this->_intensity;
};

// **** LightPoint ****

LightPoint::LightPoint(double intensity, Vec3 position) : Light(intensity), _position(position) {};

double LightPoint::Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const
{
    double coeff = direction.Dot(normal) / (normal.Norm() * direction.Norm());
    return this->_intensity * coeff;
};

// **** LightDirectional ****

LightDirectional::LightDirectional(double intensity, Vec3 direction) : Light(intensity), _direction(direction) {};

double LightDirectional::Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const
{
    double coeff = this->_direction.Dot(normal) / (normal.Norm() * this->_direction.Norm());
    return this->_intensity * coeff;
};