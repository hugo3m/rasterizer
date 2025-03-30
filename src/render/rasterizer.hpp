#pragma once

#include <vector>
#include <optional>

#include "canvas.hpp"
#include "viewport.hpp"
#include "../instances/instance.hpp"
#include "../math/vec.hpp"
#include "../math/matrix.hpp"
#include "../instances/camera.hpp"
#include "../instances/light.hpp"
#include "../enums.hpp"

using namespace std;

class Rasterizer
{
private:
    ShadingMethod _shadingMethod;

    Canvas _canvas;
    Camera _camera;

    vector<Instance> _instances;
    vector<shared_ptr<Light>> _lights;

    Matrix _matrixProjection;

    // draw without depth buffer
    void _DrawLine(const Vec2 &from, const Vec2 &to, const RGBA &color);

    void _DrawTriangleWireframe(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const RGBA &color);

    void _DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color);

    void _DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color);

    // draw with depth buffer
    void _DrawLine(Vec3 from, Vec3 to, RGBA color, const Matrix &matrixProjection);

    void _DrawTriangleWireframe(const Triangle &triangle, const RGBA &color, const Matrix &matrixProjection);

    void _DrawTriangleFilled(const Triangle &triangle, const Material &material, const Matrix &matrixProjection);

    void _DrawTriangleShaded(const Triangle &triangle, const Material &material, const Matrix &matrixProjection);

    void _DrawTriangleShadedGoureau(const Triangle &triangle, const Material &material, const Matrix &matrixProjection);

    void _DrawTriangleShadedPong(const Triangle &triangle, const Material &material, const Matrix &matrixProjection);

    // render
    void _RenderInstance(const Instance &instance);

    void _RenderTriangle(const Triangle &triangle, const Material &material, const Matrix &matrixProjection);

    // light
    double _GetLightingCoeff(const Vec3 &position, const Vec3 &normal, const Material &material) const;

public:
    Rasterizer(const int height, const int width, const ShadingMethod shadingMethod);

    vector<int> Draw() const;

    void Input(bool forward, bool backward, bool left, bool right, bool up, bool down, double deltaTime);

    void Render(const double deltaTime);
};

Matrix GenerateMatrixProjection(const Canvas &canvas, const Viewport &viewport);

vector<Instance> ClipInstancesAgainstPlanes(const vector<Instance> &instances, const array<Plane, 5> &clipPlanes);

optional<Instance> ClipInstanceAgainstPlanes(Instance instance, const array<Plane, 5> &clipPlanes);

optional<Instance> ClipInstanceAgainstPlane(const Instance &instance, const Plane &clipPlane);

vector<Triangle> ClipTrianglesAgainstPlane(const vector<shared_ptr<Triangle>> &triangles, const Plane &clipPlane);

vector<Triangle> ClipTriangleAgainstPlane(const shared_ptr<Triangle> &triangle, const Plane &clipPlane);