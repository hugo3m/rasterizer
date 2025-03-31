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
    vector<double> _depthBuffer;
    vector<int> _toCleanFlatIndexes;

    int _GetPixelFlatIndex(int x, int y) const;

    double _GetDepthValue(int x, int y) const;

    void _SetDepthValue(int x, int y, double depth);

public:
    Canvas(int height, int width);

    vector<int> Render() const;

    uint8_t *RenderNative() const;

    void Reset();

    int GetWidthMax() const;

    int GetHeightMax() const;

    void SetPixel(int x, int y, int r, int g, int b, int a, double depth);

    void SetPixel(int x, int y, int r, int g, int b, int a);

    void SetPixelFromRGBA(int x, int y, double depth, RGBA rgba);

    void SetPixelFromRGBA(int x, int y, RGBA rgba);
};