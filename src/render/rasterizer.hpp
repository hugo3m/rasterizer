#pragma once

#include "canvas.hpp"
#include "viewport.hpp"
#include "../math/vec.hpp"

class Rasterizer
{
private:
    Canvas _canvas;
    Viewport _viewport;

    void _DrawLine(Vec2 from, Vec2 to, RGBA color);

    void _DrawTriangleWireframe(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);

    void _DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);

    void _DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color);

    Vec2 _VertexToCanvas(Vec3 vertex);

    Vec3 _VertexToViewport(Vec3 vertex);

    Vec2 _ViewportToCanvas(Vec2 p_viewport);

public:
    Rasterizer();

    vector<int> Draw() const;
};