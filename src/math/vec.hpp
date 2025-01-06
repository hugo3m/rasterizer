#pragma once

#include <vector>

using namespace std;

class Vec
{
public:
    double x;

    Vec(double x);

    virtual unsigned int GetLength() const;
    virtual ~Vec();
    virtual bool operator==(const Vec &other) const;
};
class Vec2 : public Vec
{
public:
    double y;

    Vec2(double x, double y);

    virtual unsigned int GetLength() const override;

    Vec2 operator*(double const &other) const;

    Vec2 operator/(double const &other) const;

    virtual bool operator==(const Vec2 &other) const;
};
class Vec3 : public Vec2
{
public:
    double z;

    Vec3(double x, double y, double z);

    Vec3 operator+(Vec3 const &other) const;

    Vec3 operator/(double const &other) const;

    double Norm() const;

    Vec3 Normalize() const;

    double Dot(const Vec3 &other) const;

    virtual unsigned int GetLength() const override;

    virtual bool operator==(const Vec3 &other) const;
};

class VecHomogenous : public Vec3
{
public:
    double w;

    VecHomogenous(double x, double y, double z, double w);

    unsigned int GetLength() const override;
};
