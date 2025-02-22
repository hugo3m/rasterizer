#pragma once

#include "../math/matrix.hpp"

class Rotation
{
public:
    double x;
    double y;
    double z;

    Rotation(double x, double y, double z) : x(x), y(y), z(z) {};

    Matrix GenerateMatrixRotation() const;
};