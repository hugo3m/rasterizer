#include "utils.hpp"

vector<Vec2> Interpolate(Vec2 from, Vec2 to)
{
    if (from.x == to.x)
    {
        return {Vec2(to.x, to.y)};
    }
    vector<Vec2> res;
    // y = ax + b
    double a = (to.y - from.y) / (to.x - from.x);
    double y = from.y;
    for (int x = from.x; x <= to.x; ++x)
    {
        res.push_back(Vec2(x, y));
        // y(n+1) = y(n) + a
        y += a;
    }
    return res;
}