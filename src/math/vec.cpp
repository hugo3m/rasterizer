#include "vec.hpp"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z)
{
}

Vec2::Vec2(double x, double y) : x(x), y(y)
{
}

Vec3 Vec3::operator+(Vec3 const &other) const
{
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
};
