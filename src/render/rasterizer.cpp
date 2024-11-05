#include "rasterizer.hpp"
#include "../math/utils.hpp"

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200))
{
    // this->_DrawTriangleFilled(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(0, 255, 0, 255));
    this->_DrawTriangleShaded(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    this->_DrawTriangleWireframe(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
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
    vector<double> xs12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
    vector<double> xs13 = Interpolate(p1.y, p1.x, p3.y, p3.x);
    vector<double> xs23 = Interpolate(p2.y, p2.x, p3.y, p3.x);
    // merge small sides together
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // find left and right side
    vector<double> xsLeft;
    vector<double> xsRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        xsRight = xs1223;
    }
    else
    {
        xsLeft = xs1223;
        xsRight = xs13;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side
        int xLeft = xsLeft[y - p1.y];
        int xRight = xsRight[y - p1.y];
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, color);
        }
    }
}

void Rasterizer::_DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, RGBA color)
{
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
        std::swap(p1, p2);
    if (p3.y < p1.y)
        std::swap(p1, p3);
    if (p3.y < p2.y)
        std::swap(p2, p3);
    // arbitrarly choose vertex intensity
    double i1 = 1;
    double i2 = 0.5;
    double i3 = 0;
    // interpolate xs for every sides
    vector<double> xs12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
    vector<double> xs13 = Interpolate(p1.y, p1.x, p3.y, p3.x);
    vector<double> xs23 = Interpolate(p2.y, p2.x, p3.y, p3.x);
    // interpolate intensity for every height
    vector<double> is12 = Interpolate(p1.y, i1, p2.y, i2);
    vector<double> is13 = Interpolate(p1.y, i1, p3.y, i3);
    vector<double> is23 = Interpolate(p2.y, i2, p3.y, i3);
    // merge small sides together
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // merge small intensity together
    vector<double> is1223;
    is1223.insert(is1223.end(), is12.begin(), is12.end() - 1);
    is1223.insert(is1223.end(), is23.begin(), is23.end());
    // find left and right side
    vector<double> xsLeft;
    vector<double> xsRight;
    vector<double> isLeft;
    vector<double> isRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        isLeft = is13;
        xsRight = xs1223;
        isRight = is1223;
    }
    else
    {
        xsLeft = xs1223;
        isLeft = is1223;
        xsRight = xs13;
        isRight = is13;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side
        double xLeft = xsLeft[y - p1.y];
        double xRight = xsRight[y - p1.y];
        // retrieve insity left and right
        double iLeft = isLeft[y - p1.y];
        double iRight = isRight[y - p1.y];
        // interpolate intensity from left to right
        vector<double> is = Interpolate(xLeft, iLeft, xRight, iRight);
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            RGBA shadedColor = color * is[x - xLeft];
            this->_canvas.SetPixelFromRGBA(x, y, shadedColor);
        }
    }
}