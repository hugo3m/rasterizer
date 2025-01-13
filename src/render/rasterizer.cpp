#include <memory>

#include "rasterizer.hpp"
#include "../instances/transform.hpp"
#include "../math/utils.hpp"
#include "../math/triangle.hpp"
#include "../math/plane.hpp"
#include "../meshes/cube.hpp"
#include "../meshes/custom.hpp"

using namespace std;

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200)), _camera(Camera({1, 1, 1}, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(0, 0, 0)))), _matrixProjection(GenerateMatrixProjection(_canvas, _camera.GetViewport()))
{
    // // this->_DrawTriangleFilled(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // // this->_DrawTriangleShaded(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // // this->_DrawTriangleWireframe(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));

    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(1, 1, 1);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(-1, 1, 1);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(-1, -1, 1);
    shared_ptr<Vec3> v4 = make_shared<Vec3>(1, -1, 1);
    // The four "back" vertices
    shared_ptr<Vec3> v5 = make_shared<Vec3>(1, 1, -1);
    shared_ptr<Vec3> v6 = make_shared<Vec3>(-1, 1, -1);
    shared_ptr<Vec3> v7 = make_shared<Vec3>(-1, -1, -1);
    shared_ptr<Vec3> v8 = make_shared<Vec3>(1, -1, -1);
    // the triangle mesh
    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);
    shared_ptr<Triangle> t2 = make_shared<Triangle>(v1, v3, v4);
    shared_ptr<Triangle> t3 = make_shared<Triangle>(v5, v1, v2);
    shared_ptr<Triangle> t4 = make_shared<Triangle>(v5, v4, v8);
    shared_ptr<Triangle> t5 = make_shared<Triangle>(v6, v5, v8);
    shared_ptr<Triangle> t6 = make_shared<Triangle>(v6, v8, v7);
    shared_ptr<Triangle> t7 = make_shared<Triangle>(v2, v6, v7);
    shared_ptr<Triangle> t8 = make_shared<Triangle>(v2, v7, v3);
    shared_ptr<Triangle> t9 = make_shared<Triangle>(v5, v6, v2);
    shared_ptr<Triangle> t10 = make_shared<Triangle>(v5, v2, v1);
    shared_ptr<Triangle> t11 = make_shared<Triangle>(v3, v7, v8);
    shared_ptr<Triangle> t12 = make_shared<Triangle>(v3, v8, v4);
    // the cube mesh
    shared_ptr<CubeMesh> c1 = make_shared<CubeMesh>(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
    // the cube instance
    this->_instances.push_back(Instance(c1, Transform(Vec3(-1.5, 0, 7), Rotation(0, 0, 0), Vec3(1, 1, 1))));
    this->_instances.push_back(Instance(c1, Transform(Vec3(1, 0, 10), Rotation(0, 0, 45), Vec3(2, 2, 2))));

    this->_Render();
}

vector<int> Rasterizer::Draw() const
{
    return this->_canvas.Render();
}

void Rasterizer::_DrawLine(const Vec2 &from, const Vec2 &to, const RGBA &color)
{

    vector<Vec2> points = InterpolateVec2(from, to);
    for (const Vec2 &point : points)
    {
        this->_canvas.SetPixelFromRGBA(point.x, point.y, color);
    }
}

void Rasterizer::_DrawTriangleWireframe(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const RGBA &color)
{
    this->_DrawLine(p1, p2, color);
    this->_DrawLine(p2, p3, color);
    this->_DrawLine(p3, p1, color);
}

void Rasterizer::_DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color)
{
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
        std::swap(p1, p2);
    if (p3.y < p1.y)
        std::swap(p1, p3);
    if (p3.y < p2.y)
        std::swap(p2, p3);
    // interpolate xs for every sides
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // merge small sides together
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // find left and right side
    vector<double> xsLeft;
    vector<double> xsRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        xsRight = xs1223;
    }
    else
    {
        xsLeft = xs1223;
        xsRight = xs13;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side
        int xLeft = xsLeft[y - p1.y];
        int xRight = xsRight[y - p1.y];
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, color);
        }
    }
}

void Rasterizer::_DrawTriangleShaded(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color)
{
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
        std::swap(p1, p2);
    if (p3.y < p1.y)
        std::swap(p1, p3);
    if (p3.y < p2.y)
        std::swap(p2, p3);
    // arbitrarly choose vertex intensity
    double i1 = 1;
    double i2 = 0.5;
    double i3 = 0;
    // interpolate xs for every sides
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // interpolate intensity for every height
    vector<double> is12 = InterpLinear(i1, i2, p2.y - p1.y);
    vector<double> is13 = InterpLinear(i1, i3, p3.y - p1.y);
    vector<double> is23 = InterpLinear(i2, i3, p3.y - p2.y);
    // merge small sides together
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // merge small intensity together
    vector<double> is1223;
    is1223.insert(is1223.end(), is12.begin(), is12.end() - 1);
    is1223.insert(is1223.end(), is23.begin(), is23.end());
    // find left and right side
    vector<double> xsLeft;
    vector<double> xsRight;
    vector<double> isLeft;
    vector<double> isRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        isLeft = is13;
        xsRight = xs1223;
        isRight = is1223;
    }
    else
    {
        xsLeft = xs1223;
        isLeft = is1223;
        xsRight = xs13;
        isRight = is13;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side
        double xLeft = xsLeft[y - p1.y];
        double xRight = xsRight[y - p1.y];
        // retrieve insity left and right
        double iLeft = isLeft[y - p1.y];
        double iRight = isRight[y - p1.y];
        // interpolate intensity from left to right
        vector<double> is = InterpLinear(iLeft, iRight, xRight - xLeft);
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            RGBA shadedColor = color * is[x - xLeft];
            this->_canvas.SetPixelFromRGBA(x, y, shadedColor);
        }
    }
}

void Rasterizer::_Render()
{
    Matrix matrixCamera = this->_camera.GenerateMatrixCamera();
    vector<Instance> clippedInstances = ClipInstancesAgainstPlanes(this->_instances, this->_camera.GetClippingPlanes());
    for (const Instance &instance : clippedInstances)
    {
        this->_RenderInstance(instance, matrixCamera);
    }
};

void Rasterizer::_RenderInstance(const Instance &instance, const Matrix &matrixCamera)
{
    Vec3 position = instance.GetTransform().GetTranslation();
    Matrix matrixFactor = this->_matrixProjection * matrixCamera * instance.GenerateMatrixInstance();
    for (auto triangle : instance.GetMesh()->GetTriangles())
    {
        array<shared_ptr<Vec3>, 3> vertices = triangle->GetVertices();
        // multiply each vertices
        unique_ptr<Vec> v1Factored = matrixFactor * VecHomogenous((*vertices[0]).x, (*vertices[0]).y, (*vertices[0]).z, 1);
        unique_ptr<Vec> v2Factored = matrixFactor * VecHomogenous((*vertices[1]).x, (*vertices[1]).y, (*vertices[1]).z, 1);
        unique_ptr<Vec> v3Factored = matrixFactor * VecHomogenous((*vertices[2]).x, (*vertices[2]).y, (*vertices[2]).z, 1);
        // cast to vec3
        Vec3 *v1 = dynamic_cast<Vec3 *>(v1Factored.get());
        Vec3 *v2 = dynamic_cast<Vec3 *>(v2Factored.get());
        Vec3 *v3 = dynamic_cast<Vec3 *>(v3Factored.get());
        if (v1 && v2 && v3)
        {
            Vec2 fV1 = Vec2(v1->x, v1->y) * (1 / v1->z);
            Vec2 fV2 = Vec2(v2->x, v2->y) * (1 / v2->z);
            Vec2 fV3 = Vec2(v3->x, v3->y) * (1 / v3->z);
            this->_DrawTriangleWireframe(fV1, fV2, fV3, RGBA(255, 120, 200, 255));
        }
    }
};

Matrix GenerateMatrixProjection(const Canvas &canvas, const Viewport &viewport)
{
    double widthRatio = (viewport.depth * canvas.GetWidthMax() * 2) / viewport.width;
    double heightRatio = (viewport.depth * canvas.GetHeightMax() * 2) / viewport.height;
    return Matrix({widthRatio, 0, 0, 0, 0, heightRatio, 0, 0, 0, 0, 1, 0}, 3, 4);
}

vector<Instance> ClipInstancesAgainstPlanes(const vector<Instance> &instances, const array<Plane, 5> &clipPlanes)
{
    vector<Instance> res;
    for (const auto instance : instances)
    {
        optional<Instance> clippedInstance = ClipInstanceAgainstPlanes(instance, clipPlanes);
        if (clippedInstance)
        {
            res.push_back(clippedInstance.value());
        }
    }
    return res;
};

optional<Instance> ClipInstanceAgainstPlanes(const Instance &instance, const array<Plane, 5> &clipPlanes)
{
    Instance res = instance;
    for (const auto clipPlane : clipPlanes)
    {
        optional<Instance> optInstance = ClipInstanceAgainstPlane(instance, clipPlane);
        if (!optInstance)
        {
            return {};
        }
        res = optInstance.value();
    }
    return res;
}

optional<Instance> ClipInstanceAgainstPlane(const Instance &instance, const Plane &clipPlane)
{
    Sphere boundingSphere = instance.GetMesh()->GetBoundingSphere();
    double radius = boundingSphere.GetRadius();
    double signedDistance = clipPlane.SignedDist(boundingSphere.GetCenter());
    if (signedDistance > radius)
    {
        return instance;
    }
    if (signedDistance < -radius)
    {
        return {};
    }
    vector<shared_ptr<Triangle>> triangles = ClipTrianglesAgainstPlane(instance.GetMesh()->GetTriangles(), clipPlane);
    return Instance(make_shared<CustomMesh>(triangles), instance.GetTransform());
}

vector<shared_ptr<Triangle>> ClipTrianglesAgainstPlane(const vector<shared_ptr<Triangle>> &triangles, const Plane &clipPlane)
{
    vector<shared_ptr<Triangle>> res;
    for (const auto triangle : triangles)
    {
        vector<shared_ptr<Triangle>> clippedTriangles = ClipTriangleAgainstPlane(triangle, clipPlane);
        for (const auto clippedTriangle : clippedTriangles)
        {
            res.push_back(clippedTriangle);
        }
    }
    return res;
};

vector<shared_ptr<Triangle>> ClipTriangleAgainstPlane(const shared_ptr<Triangle> &triangle, const Plane &clipPlane)
{
    vector<shared_ptr<Triangle>> res;

    array<shared_ptr<Vec3>, 3> vertices = triangle->GetVertices();
    shared_ptr<Vec3> v1 = vertices[0];
    shared_ptr<Vec3> v2 = vertices[1];
    shared_ptr<Vec3> v3 = vertices[2];
    double d1 = clipPlane.SignedDist(*v1);
    double d2 = clipPlane.SignedDist(*v2);
    double d3 = clipPlane.SignedDist(*v3);
    // if all distance positive
    if (d1 >= 0 && d2 >= 0 && d3 >= 0)
    {
        // just current triangle
        res.push_back(triangle);
    }
    // if only one distance positive
    if ((d1 >= 0 && d2 < 0 && d3 < 0) || (d2 >= 0 && d1 < 0 && d3 < 0) || (d3 >= 0 && d1 < 0 && d2 < 0))
    {
        // find out which one
        shared_ptr<Vec3> positive;
        shared_ptr<Vec3> negative1;
        shared_ptr<Vec3> negative2;
        if (d1 >= 0)
        {
            positive = v1;
            negative1 = v2;
            negative2 = v3;
        }
        if (d2 >= 0)
        {
            positive = v2;
            negative1 = v1;
            negative2 = v3;
        }
        if (d3 >= 0)
        {
            positive = v3;
            negative1 = v1;
            negative2 = v2;
        }
        Vec3 positive1 = clipPlane.Intersection(*positive, *negative1);
        Vec3 positive2 = clipPlane.Intersection(*positive, *negative2);
        res.push_back(make_shared<Triangle>(positive, make_shared<Vec3>(positive1.x, positive1.y, positive1.z), make_shared<Vec3>(positive2.x, positive2.y, positive2.z)));
    }
    // if only one distance negative
    if ((d1 >= 0 && d2 >= 0 && d3 < 0) || (d1 >= 0 && d3 >= 0 && d2 < 0) || (d2 >= 0 && d3 >= 0 && d1 < 0))
    {
        // find out which one
        shared_ptr<Vec3> negative;
        shared_ptr<Vec3> positive1;
        shared_ptr<Vec3> positive2;
        if (d1 < 0)
        {
            negative = v1;
            positive1 = v2;
            positive2 = v3;
        }
        if (d2 < 0)
        {
            negative = v2;
            positive1 = v1;
            positive2 = v3;
        }
        if (d3 < 0)
        {
            negative = v3;
            positive1 = v1;
            positive2 = v2;
        }
        Vec3 npositive1 = clipPlane.Intersection(*positive1, *negative);
        Vec3 npositive2 = clipPlane.Intersection(*positive2, *negative);
        shared_ptr<Vec3> ptr_npositive1 = make_shared<Vec3>(npositive1.x, npositive1.y, npositive1.z);
        res.push_back(make_shared<Triangle>(positive1, positive2, ptr_npositive1));
        res.push_back(make_shared<Triangle>(ptr_npositive1, positive2, make_shared<Vec3>(npositive2.x, npositive2.y, npositive2.z)));
    }
    return res;
}