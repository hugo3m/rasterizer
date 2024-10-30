#include "canvas.hpp"

Canvas::Canvas(int height, int width) : _height(height), _width(width)
{
    for (int i = 0; i < height * width; i++)
    {
        this->_pixels.push_back(RGBA(0, 255, 255, 255));
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