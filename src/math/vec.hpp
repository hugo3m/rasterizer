#pragma once

class Vec3
{
public:
    double x;
    double y;
    double z;

    Vec3(double x, double y, double z);

    Vec3 operator+(Vec3 const &other) const;
};

class Vec2
{
public:
    double x;
    double y;

    Vec2(double x, double y);
};
