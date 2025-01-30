#include "light.hpp"
#include <math.h>

// **** Light ****
Light::Light(double intensity) : _intensity(intensity) {};

double Light::GetIntensity() const
{
    return this->_intensity;
}

double _GetSpecularCoeff(const Material &material, const Vec3 &lightDirection, const Vec3 &targetDirection, const Vec3 &normal)
{
    double specular = material.GetSpecular();
    if (specular <= 0)
    {
        return 0;
    }
    // direction from light to point
    // direction from camera to point
    Vec3 reflected = Reflection(lightDirection, normal);
    // let reflected = reflection(&direction, &info.normal);
    double coeff = reflected.Dot(targetDirection) / (reflected.Norm() * targetDirection.Norm());
    return powf(coeff, specular);
}

// **** LightAmbient ****

LightAmbient::LightAmbient(double intensity) : Light(intensity) {};

double LightAmbient::Diffuse(const Vec3 &direction, const Vec3 &normal) const
{
    return this->_intensity;
};

double LightAmbient::GetLightingCoeff(const Material &material, const Vec3 &point, const Vec3 &cameraPosition, const Vec3 &normal) const
{
    // input does not matter here
    return this->Diffuse(point, normal);
};

// **** LightPoint ****

LightPoint::LightPoint(double intensity, Vec3 position) : Light(intensity), _position(position) {};

double LightPoint::Diffuse(const Vec3 &direction, const Vec3 &normal) const
{
    double coeff = (direction * -1).Dot(normal) / (normal.Norm() * direction.Norm());
    return this->_intensity * coeff;
};

double LightPoint::Specular(const Material &material, const Vec3 &direction, const Vec3 &target, const Vec3 &normal) const
{
    return this->_intensity * _GetSpecularCoeff(material, direction, target, normal);
};

double LightPoint::GetLightingCoeff(const Material &material, const Vec3 &position, const Vec3 &cameraPosition, const Vec3 &normal) const
{
    double coeff = 0;
    Vec3 lightToPosition = position - this->_position;
    coeff += this->Diffuse(lightToPosition, normal);
    coeff += this->Specular(material, lightToPosition, cameraPosition - position, normal);
    return coeff;
};

// **** LightDirectional ****

LightDirectional::LightDirectional(double intensity, Vec3 direction) : Light(intensity), _direction(direction) {};

double LightDirectional::Diffuse(const Vec3 &direction, const Vec3 &normal) const
{
    double coeff = (this->_direction * -1).Dot(normal) / (normal.Norm() * this->_direction.Norm());
    return this->_intensity * coeff;
};

double LightDirectional::Specular(const Material &material, const Vec3 &targetDirection, const Vec3 &normal) const
{
    return this->_intensity * _GetSpecularCoeff(material, this->_direction, targetDirection, normal);
};

double LightDirectional::GetLightingCoeff(const Material &material, const Vec3 &position, const Vec3 &cameraPosition, const Vec3 &normal) const
{
    double coeff = 0;
    coeff += this->Diffuse(this->_direction, normal);
    coeff += this->Specular(material, cameraPosition - position, normal);
    return coeff;
};