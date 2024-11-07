#include "utils.hpp"

using namespace std;

vector<Vec2> InterpolateVec2(Vec2 from, Vec2 to)
{
    vector<Vec2> res;
    // if line horizontal-ish
    if (abs(to.x - from.x) > abs(to.y - from.y))
    {
        if (from.x > to.x)
        {
            swap(from, to);
        }
        // y = ax + b
        double a = (to.y - from.y) / (to.x - from.x);
        double y = from.y;
        for (int x = from.x; x <= to.x; x++)
        {
            res.push_back(Vec2(x, y));
            // y(n+1) = y(n) + a
            y += a;
        }
    }
    // else line vertical-ish
    else
    {
        if (from.y > to.y)
        {
            swap(from, to);
        }
        // x = ay + b
        double a = (to.x - from.x) / (to.y - from.y);
        double x = from.x;
        for (int y = from.y; y <= to.y; y++)
        {
            res.push_back(Vec2(x, y));
            // x(n+1) = x(n) + a
            x += a;
        }
    }
    return res;
}

vector<double> Interpolate(double intervalBegin, double valueBegin, double intervalEnd, double valueEnd)
{
    vector<double> res;
    if (intervalBegin > intervalEnd)
    {
        swap(intervalBegin, intervalEnd);
        swap(valueBegin, valueEnd);
    }
    // descent
    double d = (valueEnd - valueBegin) / (intervalEnd - intervalBegin);
    double y = valueBegin;
    for (int x = intervalBegin; x <= intervalEnd; x++)
    {
        res.push_back(y);
        // y(n+1) = y(n) + d
        y += d;
    }
    return res;
}

vector<double> InterpLinear(double start, double end, double steps)
{
    vector<double> res;
    if (steps < 0)
    {
        swap(start, end);
        steps = -steps;
    }
    // descent
    double d = (end - start) / steps;
    double y = start;
    for (int x = 0; x <= steps; x++)
    {
        res.push_back(y);
        // y(n+1) = y(n) + d
        y += d;
    }
    return res;
}