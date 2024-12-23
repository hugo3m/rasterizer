#include "vec.hpp"

Vec::~Vec() {
};

Vec2::Vec2(double x, double y) : x(x), y(y) {};

unsigned int Vec2::GetLength() const
{
    return 2;
};

Vec2 Vec2::operator*(double const &other) const
{
    return Vec2(this->x * other, this->y * other);
}

Vec2 Vec2::operator/(double const &other) const
{
    return Vec2(this->x / other, this->y / other);
}

Vec3::Vec3(double x, double y, double z) : Vec2(x, y), z(z) {};

unsigned int Vec3::GetLength() const
{
    return Vec2::GetLength() + 1;
};

Vec3 Vec3::operator+(Vec3 const &other) const
{
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
};

VecHomogenous::VecHomogenous(double x, double y, double z, double w) : Vec3(x, y, z), w(w) {};

unsigned int VecHomogenous::GetLength() const
{
    return Vec3::GetLength() + 1;
};

Vec3 Vec3::operator/(double const &other) const
{
    return Vec3(this->x / other, this->y / other, this->z / other);
}

double Vec3::Norm() const
{
    return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vec3 Vec3::Normalize() const
{
    return (*this) / this->Norm();
}
