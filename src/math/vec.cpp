#include "vec.hpp"

Vec3::Vec3(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

double Vec3::getX()
{
    return this->_x;
}

double Vec3::getY()
{
    return this->_y;
}

double Vec3::getZ()
{
    return this->_z;
}