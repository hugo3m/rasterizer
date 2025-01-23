#pragma once

#include "../math/vec.hpp"

class Light
{
protected:
    double _intensity;

public:
    Light(double intensity);

    virtual double GetIntensity() const;

    virtual double Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const = 0;
};

class LightAmbient : public Light
{
public:
    LightAmbient(double intensity);

    double Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const override;
};

class LightPoint : public Light
{
private:
    Vec3 _position;

public:
    LightPoint(double intensity, Vec3 position);

    double Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const override;
};

class LightDirectional : public Light
{
private:
    Vec3 _direction;

public:
    LightDirectional(double intensity, Vec3 direction);

    double Diffuse(const Vec3 &direction, const Vec3 &position, const Vec3 &normal) const override;
};
