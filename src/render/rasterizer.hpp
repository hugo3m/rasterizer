#pragma once

#include "canvas.hpp"
#include "../math/vec.hpp"

class Rasterizer
{
private:
    Canvas _canvas;
    void _DrawLine(Vec2 from, Vec2 to, RGBA color);

public:
    Rasterizer();

    vector<int> Draw() const;
};