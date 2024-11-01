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
    this->_DrawTriangleFilled(Vec2(0, -50), Vec2(50, -25), Vec2(10, 0), RGBA(0, 0, 0, 255));
}

vector<int> Rasterizer::Draw() const
{
    return this->_canvas.Render();
}

void Rasterizer::_DrawLine(Vec2 from, Vec2 to, RGBA color)
{

    vector<Vec2> points = InterpolateVec2(from, to);
    for (const Vec2 &point : points)
    {
        this->_canvas.SetPixelFromRGBA(point.x, point.y, color);
    }
}

void Rasterizer::_DrawTriangleWireframe(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color)
{
    this->_DrawLine(p1, p2, color);
    this->_DrawLine(p2, p3, color);
    this->_DrawLine(p3, p1, color);
}

void Rasterizer::_DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color)
{
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
        std::swap(p1, p2);
    if (p3.y < p1.y)
        std::swap(p1, p3);
    if (p3.y < p2.y)
        std::swap(p2, p3);
    // interpolate xs for every sides
    vector<int> xP1ToP2s = InterpolateX(p1, p2);
    vector<int> xP1ToP3s = InterpolateX(p1, p3);
    vector<int> xP2ToP3s = InterpolateX(p2, p3);
    // merge small sides together
    xP1ToP2s.pop_back();
    vector<int> xP1ToP2AndP2ToP3s;
    xP1ToP2AndP2ToP3s.insert(xP1ToP2AndP2ToP3s.end(), xP1ToP2s.begin(), xP1ToP2s.end());
    xP1ToP2AndP2ToP3s.insert(xP1ToP2AndP2ToP3s.end(), xP2ToP3s.begin(), xP2ToP3s.end());
    // find left and right side
    vector<int> xLeftSide;
    vector<int> xRightSide;
    int middle = std::floor(xP1ToP2AndP2ToP3s.size() / 2);
    if (xP1ToP3s[middle] < xP1ToP2AndP2ToP3s[middle])
    {
        xLeftSide = xP1ToP3s;
        xRightSide = xP1ToP2AndP2ToP3s;
    }
    else
    {
        xLeftSide = xP1ToP2AndP2ToP3s;
        xRightSide = xP1ToP3s;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side
        int leftX = xLeftSide[y - p1.y];
        int rightX = xRightSide[y - p1.y];
        // draw a line from left to right
        for (int x = leftX; x <= rightX; x++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, color);
        }
    }
}