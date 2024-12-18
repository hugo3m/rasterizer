#pragma once

#include <vector>

using namespace std;

class Vec
{
public:
    virtual unsigned int GetLength() const = 0;
};
class Vec2 : public Vec
{
public:
    double x;
    double y;

    Vec2(double x, double y);

    virtual unsigned int GetLength() const override;

    Vec2 operator*(double const &other) const;
};
class Vec3 : public Vec2
{
public:
    double z;

    Vec3(double x, double y, double z);

    Vec3 operator+(Vec3 const &other) const;

    unsigned int GetLength() const override;
};

class VecHomogenous : public Vec3
{
public:
    double w;

    VecHomogenous(double x, double y, double z, double w);

    unsigned int GetLength() const override;
};
