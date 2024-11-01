#include "utils.hpp"

vector<Vec2> InterpolateVec2(Vec2 from, Vec2 to)
{
    vector<Vec2> res;
    // if line horizontal-ish
    if (std::abs(to.x - from.x) - std::abs(to.y - from.y))
    {
        if (from.x > to.x)
        {
            std::swap(from, to);
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
            std::swap(from, to);
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

vector<int> InterpolateX(Vec2 from, Vec2 to)
{
    vector<int> res;
    if (from.y > to.y)
    {
        std::swap(from, to);
    }
    // x = ay + b
    double a = (to.x - from.x) / (to.y - from.y);
    double x = from.x;
    for (int y = from.y; y <= to.y; y++)
    {
        res.push_back(x);
        // x(n+1) = x(n) + a
        x += a;
    }
    return res;
}

vector<int> InterpolateY(Vec2 from, Vec2 to)
{
    vector<int> res;
    if (from.x > to.x)
    {
        std::swap(from, to);
    }
    // x = ay + b
    double a = (to.x - from.x) / (to.y - from.y);
    double y = from.y;
    for (int x = from.x; x <= to.x; x++)
    {
        res.push_back(y);
        // y(n+1) = y(n) + a
        y += a;
    }
    return res;
}