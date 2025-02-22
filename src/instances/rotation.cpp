#include "rotation.hpp"
#include "math.h"

Matrix Rotation::GenerateMatrixRotation() const
{
    const double cosX = cos(this->x * M_PI / 180);
    const double sinX = sin(this->x * M_PI / 180);

    const double cosY = cos(this->y * M_PI / 180);
    const double sinY = sin(this->y * M_PI / 180);

    const double cosZ = cos(this->z * M_PI / 180);
    const double sinZ = sin(this->z * M_PI / 180);

    // Rotation matrix around X-axis
    Matrix rotX = Matrix({1, 0, 0, 0, 0, cosX, sinX, 0, 0, -sinX, cosX, 0, 0, 0, 0, 1}, 4, 4);

    // Rotation matrix around Y-axis
    Matrix rotY = Matrix({cosY, 0, -sinY, 0, 0, 1, 0, 0, sinY, 0, cosY, 0, 0, 0, 0, 1}, 4, 4);

    // Rotation matrix around Z-axis
    Matrix rotZ = Matrix({cosZ, -sinZ, 0, 0, sinZ, cosZ, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);

    return rotZ * (rotY * rotX);
}