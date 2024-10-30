#include "rasterizer.hpp"
#include "../math/utils.hpp"

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200))
{
    for (int x = -10; x < 10; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            this->_canvas.SetPixel(x, y, 255, 0, 0, 255);
        }
    }
    this->_DrawLine(Vec2(-70, -70), Vec2(10, 30), RGBA(0, 0, 0, 255));
}

vector<int> Rasterizer::Draw() const
{
    return this->_canvas.Render();
}

void Rasterizer::_DrawLine(Vec2 from, Vec2 to, RGBA color)
{
    if (std::abs(to.x - from.x) > std::abs(to.y - from.y))
    {
        if (from.x > to.x)
        {
            std::swap(from, to);
        }
        vector<Vec2> points = Interpolate(from, to);
        for (const Vec2 &point : points)
        {
            this->_canvas.SetPixelFromRGBA(point.x, point.y, color);
        }
    }
    else
    {
        if (from.y > to.y)
        {
            std::swap(from, to);
        }
        vector<Vec2> points = Interpolate(Vec2(from.y, from.x), Vec2(to.y, to.x));
        for (const Vec2 &point : points)
        {
            this->_canvas.SetPixelFromRGBA(point.x, point.y, color);
        }
    }
}