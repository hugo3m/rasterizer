#include "rasterizer.hpp"

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200))
{
}

vector<int> Rasterizer::Draw()
{
    return this->_canvas.Render();
}