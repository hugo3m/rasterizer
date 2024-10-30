#pragma once

#include <vector>
#include "rgba.hpp"

using namespace std;

class Canvas
{
private:
    int _height;
    int _width;
    vector<RGBA> _pixels;

    int _GetPixelFlatIndex(int x, int y) const;

public:
    Canvas(int height, int width);
    vector<int> Render() const;
    int GetWidthMax() const;
    int GetHeightMax() const;
    void SetPixel(int x, int y, int r, int g, int b, int a);
    void SetPixelFromRGBA(int x, int y, RGBA rgba);
};