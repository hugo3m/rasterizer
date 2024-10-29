#include "canvas.hpp"

Canvas::Canvas(int height, int width) : _height(height), _width(width)
{
    for (int i = 0; i < height * width; i++)
    {
        this->_pixels.push_back(RGBA(0, 255, 255, 255));
    }
}

void Canvas::Render(vector<int> &res) const
{
    int i = 0;
    for (const RGBA &rgba : this->_pixels)
    {
        array<int, 4> flat = rgba.Unpack();
        res[i] = flat[0];
        res[i + 1] = flat[1];
        res[i + 2] = flat[2];
        res[i + 3] = flat[3];
        i += 4;
    }
}