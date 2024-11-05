#pragma once

#include "canvas.hpp"
#include "../math/vec.hpp"

class Rasterizer
{
private:
    Canvas _canvas;
    void _DrawLine(Vec2 from, Vec2 to, RGBA color);
    void _DrawTriangleWireframe(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);
    void _DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);
    void _DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);

public:
    Rasterizer();

    vector<int> Draw() const;
};