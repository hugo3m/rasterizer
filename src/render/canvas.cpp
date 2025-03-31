#include "canvas.hpp"
#include <algorithm>

using namespace std;

Canvas::Canvas(int height, int width) : _height(height), _width(width)
{
    for (int i = 0; i < this->_height * this->_width; i++)
    {
        this->_pixels.push_back(RGBA(255, 255, 255, 255));
        this->_depthBuffer.push_back(0);
    }
}

vector<int> Canvas::Render() const
{
    vector<int> res;
    for (const RGBA &rgba : this->_pixels)
    {
        array<int, 4> flat = rgba.Unpack();
        res.push_back(flat[0]);
        res.push_back(flat[1]);
        res.push_back(flat[2]);
        res.push_back(flat[3]);
    }
    return res;
}

uint8_t *Canvas::RenderNative() const
{
    uint8_t *res = new uint8_t[this->_pixels.size() * 4];
    for (int i = 0; i < this->_pixels.size(); i++)
    {
        array<int, 4> flat = this->_pixels[i].Unpack();
        res[(i * 4) + 0] = static_cast<uint8_t>(flat[0]);
        res[(i * 4) + 1] = static_cast<uint8_t>(flat[1]);
        res[(i * 4) + 2] = static_cast<uint8_t>(flat[2]);
        res[(i * 4) + 3] = static_cast<uint8_t>(flat[3]);
    }
    return res;
}

int Canvas::_GetPixelFlatIndex(int x, int y) const
{
    int x_index = x + this->GetWidthMax();
    int y_index = this->GetHeightMax() - y;
    return (y_index * this->_width) + x_index;
}

int Canvas::GetHeightMax() const
{
    return this->_height / 2;
}

int Canvas::GetWidthMax() const
{
    return this->_width / 2;
}

void Canvas::SetPixel(int x, int y, int r, int g, int b, int a, double depth)
{
    this->SetPixelFromRGBA(x, y, depth, RGBA(r, g, b, a));
}

void Canvas::SetPixel(int x, int y, int r, int g, int b, int a)
{
    this->SetPixelFromRGBA(x, y, RGBA(r, g, b, a));
}

void Canvas::SetPixelFromRGBA(int x, int y, double depth, RGBA rgba)
{
    if (x <= -this->GetWidthMax() || x >= this->GetWidthMax() || y <= -this->GetWidthMax() || y >= this->GetHeightMax())
    {
        return;
    }
    if (depth > this->_GetDepthValue(x, y))
    {
        this->_SetDepthValue(x, y, depth);
        this->SetPixelFromRGBA(x, y, rgba);
        this->_toCleanFlatIndexes.push_back(_GetPixelFlatIndex(x, y));
    }
}

void Canvas::SetPixelFromRGBA(int x, int y, RGBA rgba)
{
    this->_pixels[this->_GetPixelFlatIndex(x, y)].Set(rgba);
}

double Canvas::_GetDepthValue(int x, int y) const
{
    return this->_depthBuffer[this->_GetPixelFlatIndex(x, y)];
}

void Canvas::_SetDepthValue(int x, int y, double depth)
{
    this->_depthBuffer[this->_GetPixelFlatIndex(x, y)] = depth;
}

void Canvas::Reset()
{
    while (!this->_toCleanFlatIndexes.empty())
    {
        const int toCleanFlatIndex = this->_toCleanFlatIndexes.back();
        this->_pixels[toCleanFlatIndex].Set(RGBA(255, 255, 255, 255));
        this->_depthBuffer[toCleanFlatIndex] = 0;
        this->_toCleanFlatIndexes.pop_back();
    }
}