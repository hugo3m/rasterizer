#include "vec.hpp"

// **** Vec ****

Vec::Vec(double x) : x(x) {};

Vec::~Vec() {
};

bool Vec::operator==(const Vec &other) const
{
    return this->x == other.x;
}

unsigned int Vec::GetLength() const
{
    return 1;
}

Vec Vec::operator-(const Vec &other) const
{
    return Vec(this->x - other.x);
}

Vec Vec::operator*(double const &other) const
{
    return Vec(this->x * other);
}

// **** Vec2 ****

Vec2::Vec2(double x, double y) : Vec(x), y(y) {};

unsigned int Vec2::GetLength() const
{
    return Vec::GetLength() + 1;
};

Vec2 Vec2::operator*(double const &other) const
{
    return Vec2(this->x * other, this->y * other);
}

Vec2 Vec2::operator/(double const &other) const
{
    return Vec2(this->x / other, this->y / other);
}

bool Vec2::operator==(const Vec2 &other) const
{
    return this->x == other.x && this->y == other.y;
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(this->x - other.x, this->y - other.y);
}

// **** Vec3 ****

Vec3::Vec3(double x, double y, double z) : Vec2(x, y), z(z) {};

Vec3::Vec3(const Vec3 &vec3) : Vec2(vec3.x, vec3.y), z(vec3.z) {};

unsigned int Vec3::GetLength() const
{
    return Vec2::GetLength() + 1;
};

Vec3 Vec3::operator+(Vec3 const &other) const
{
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
};

bool Vec3::operator==(const Vec3 &other) const
{
    return this->x == other.x && this->y == other.y && this->z == other.z;
};

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
};

Vec3 Vec3::operator*(double const &other) const
{
    return Vec3(this->x * other, this->y * other, this->z * other);
}

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
    double norm = this->Norm();
    return norm > 0 ? (*this) / this->Norm() : (*this);
}

double Vec3::Dot(const Vec3 &other) const
{
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

Vec3 Vec3::CrossProduct(const Vec3 &other) const
{
    return Vec3((this->y * other.z) - (this->z * other.y), (this->z * other.x) - (this->x * other.z), (this->x * other.y) - (this->y * other.x));
}

Vec3 Reflection(const Vec3 &direction, const Vec3 &normal)
{
    return direction - (normal * 2.0 * normal.Dot(direction));
}

Vec3 Vec3::ToVec3() const
{
    return Vec3(this->x, this->y, this->z);
}

// **** VecHomogenous ****

VecHomogenous::VecHomogenous(double x, double y, double z, double w) : Vec3(x, y, z), w(w) {};

unsigned int VecHomogenous::GetLength() const
{
    return Vec3::GetLength() + 1;
};

Vec3 VecHomogenous::ToVec3() const
{
    if (this->w != 0)
    {
        return Vec3(this->x / this->w, this->y / this->w, this->z / this->w);
    }
    return Vec3(this->x, this->y, this->z);
}
