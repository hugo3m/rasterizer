#include "canvas.hpp"

class Rasterizer
{
private:
    Canvas _canvas;

public:
    Rasterizer();

    vector<int> Draw();
};