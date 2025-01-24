#pragma once

#include "rgba.hpp"

class Material
{
private:
    RGBA _color;

    double _specular;

    double _reflective;

public:
    Material(RGBA color, double specular, double reflective);

    RGBA GetColor() const;

    double GetSpecular() const;

    double GetReflective() const;
};