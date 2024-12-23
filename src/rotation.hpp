#pragma once

class Rotation
{
public:
    double yaw;
    double pitch;
    double roll;

    Rotation(double yaw, double pitch, double roll) : yaw(yaw), pitch(pitch), roll(roll) {};
};