#pragma once

#include <vector>
#include <optional>

#include "canvas.hpp"
#include "viewport.hpp"
#include "../instances/instance.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"
#include "../instances/camera.hpp"

using namespace std;

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

vector<Instance> ClipInstancesAgainstPlanes(const vector<Instance> &instances, const array<Plane, 5> &clipPlanes);

optional<Instance> ClipInstanceAgainstPlanes(const Instance &instance, const array<Plane, 5> &clipPlanes);

optional<Instance> ClipInstanceAgainstPlane(const Instance &instance, const Plane &clipPlane);

vector<shared_ptr<Triangle>> ClipTrianglesAgainstPlane(const vector<shared_ptr<Triangle>> &triangles, const Plane &clipPlane);

vector<shared_ptr<Triangle>> ClipTriangleAgainstPlane(const shared_ptr<Triangle> &triangle, const Plane &clipPlane);