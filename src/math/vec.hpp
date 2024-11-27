#pragma once

class Vec2
{
public:
    double x;
    double y;

    Vec2(double x, double y);

    unsigned int GetLength() const;
};
class Vec3 : public Vec2
{
public:
    double z;

    Vec3(double x, double y, double z);

    Vec3 operator+(Vec3 const &other) const;

    unsigned int GetLength() const;
};

class VecHomogenous : public Vec3
{
public:
    double w;

    VecHomogenous(double x, double y, double z, double w);

    unsigned int GetLength() const;
};
