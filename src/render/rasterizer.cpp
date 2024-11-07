#include "rasterizer.hpp"
#include "../math/utils.hpp"

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200)), _viewport({1, 1, 1})
{
    // this->_DrawTriangleFilled(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // this->_DrawTriangleShaded(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // this->_DrawTriangleWireframe(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));

    // The four "front" vertices
    Vec3 vAf(-2, -0.5, 5);
    Vec3 vBf(-2, 0.5, 5);
    Vec3 vCf(-1, 0.5, 5);
    Vec3 vDf(-1, -0.5, 5);

    // The four "back" vertices
    Vec3 vAb(-2, -0.5, 6);
    Vec3 vBb(-2, 0.5, 6);
    Vec3 vCb(-1, 0.5, 6);
    Vec3 vDb(-1, -0.5, 6);

    RGBA Red(255, 0, 0, 255);
    RGBA Blue(0, 0, 255, 255);
    RGBA Green(0, 255, 0, 255);

    // The front face
    _DrawLine(_VertexToCanvas(vAf), _VertexToCanvas(vBf), Blue);
    _DrawLine(_VertexToCanvas(vBf), _VertexToCanvas(vCf), Blue);
    _DrawLine(_VertexToCanvas(vCf), _VertexToCanvas(vDf), Blue);
    _DrawLine(_VertexToCanvas(vDf), _VertexToCanvas(vAf), Blue);

    // The back face
    _DrawLine(_VertexToCanvas(vAb), _VertexToCanvas(vBb), Red);
    _DrawLine(_VertexToCanvas(vBb), _VertexToCanvas(vCb), Red);
    _DrawLine(_VertexToCanvas(vCb), _VertexToCanvas(vDb), Red);
    _DrawLine(_VertexToCanvas(vDb), _VertexToCanvas(vAb), Red);

    // The front-to-back edges
    _DrawLine(_VertexToCanvas(vAf), _VertexToCanvas(vAb), Green);
    _DrawLine(_VertexToCanvas(vBf), _VertexToCanvas(vBb), Green);
    _DrawLine(_VertexToCanvas(vCf), _VertexToCanvas(vCb), Green);
    _DrawLine(_VertexToCanvas(vDf), _VertexToCanvas(vDb), Green);
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
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
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
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // interpolate intensity for every height
    vector<double> is12 = InterpLinear(i1, i2, p2.y - p1.y);
    vector<double> is13 = InterpLinear(i1, i3, p3.y - p1.y);
    vector<double> is23 = InterpLinear(i2, i3, p3.y - p2.y);
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
        vector<double> is = InterpLinear(iLeft, iRight, xRight - xLeft);
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            RGBA shadedColor = color * is[x - xLeft];
            this->_canvas.SetPixelFromRGBA(x, y, shadedColor);
        }
    }
}

Vec2 Rasterizer::_ViewportToCanvas(Vec2 p_viewport)
{
    double width_ratio = (this->_canvas.GetWidthMax() * 2) / this->_viewport.width;
    double height_ratio = (this->_canvas.GetHeightMax() * 2) / this->_viewport.height;
    return Vec2(p_viewport.x * width_ratio, p_viewport.y * height_ratio);
}

Vec3 Rasterizer::_VertexToViewport(Vec3 vertex)
{
    double ratio = this->_viewport.depth / vertex.z;
    return Vec3(vertex.x * ratio, vertex.y * ratio, this->_viewport.depth);
}

Vec2 Rasterizer::_VertexToCanvas(Vec3 vertex)
{
    Vec3 vertex_to_viewport = this->_VertexToViewport(vertex);
    return this->_ViewportToCanvas(Vec2(vertex_to_viewport.x, vertex_to_viewport.y));
}