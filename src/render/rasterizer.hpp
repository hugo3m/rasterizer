#pragma once

#include <vector>

#include "canvas.hpp"
#include "viewport.hpp"
#include "../instances/instance.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"
#include "../instances/camera.hpp"

class Rasterizer
{
private:
    Canvas _canvas;
    Camera _camera;

    vector<Instance> _instances;

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

Matrix GenerateMatrixProjection(const Canvas &canvas, const Viewport &viewport);

Matrix GenerateMatrixInstance(const Instance &canvas);

Matrix GenerateMatrixRotation(const Rotation &rotation);

vector<Instance> ClipInstances(const vector<Instance> &instances);