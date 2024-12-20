#pragma once

#include <vector>

#include "canvas.hpp"
#include "viewport.hpp"
#include "../instance.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"

class Rasterizer
{
private:
    Canvas _canvas;
    vector<Instance> _instances;
    Viewport _viewport;
    Transform _camera;

    Matrix _matrixProjection;

    void _DrawLine(const Vec2 &from, const Vec2 &to, const RGBA &color);

    void _DrawTriangleWireframe(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const RGBA &color);

    void _DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color);

    void _DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color);

    void _Render();

    void _RenderInstance(const Instance &instance, const Matrix &matrixCamera);

public:
    Rasterizer();

    vector<int> Draw() const;
};

Matrix GenerateMatrixCamera(const Transform &camera);

Matrix GenerateMatrixProjection(const Canvas &canvas, const Viewport &viewport);

Matrix GenerateMatrixInstance(const Instance &canvas);