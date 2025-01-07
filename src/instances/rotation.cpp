#include "rotation.hpp"

Matrix Rotation::GenerateMatrixRotation() const
{
    double yaw = this->yaw;
    double pitch = this->pitch;
    double roll = this->roll;

    return Matrix({cos(yaw) * cos(pitch),
                   (cos(yaw) * sin(pitch) * sin(roll)) - (sin(yaw) * cos(roll)),
                   (cos(yaw) * sin(pitch) * cos(roll)) + (sin(yaw) * sin(roll)),
                   0,
                   sin(yaw) * cos(pitch),
                   (sin(yaw) * sin(pitch) * sin(roll)) + (cos(yaw) * cos(roll)),
                   (sin(yaw) * sin(pitch) * cos(roll)) - (cos(yaw) * sin(roll)),
                   0,
                   -sin(pitch),
                   cos(pitch) * sin(roll),
                   cos(pitch) * cos(roll),
                   0,
                   0,
                   0,
                   0,
                   1},
                  4, 4);
}