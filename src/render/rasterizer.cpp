#include <memory>

#include "rasterizer.hpp"
#include "../instances/transform.hpp"
#include "../math/utils.hpp"
#include "../math/triangle.hpp"
#include "../math/plane.hpp"
#include "../meshes/cube.hpp"
#include "../meshes/triangle.hpp"
#include "../meshes/custom.hpp"

using namespace std;

Rasterizer::Rasterizer() : _canvas(Canvas(200, 200)), _camera(Camera({1, 1, 1}, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(0, 0, 0)))), _matrixProjection(GenerateMatrixProjection(_canvas, _camera.GetViewport()))
{
    // // this->_DrawTriangleFilled(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // // this->_DrawTriangleShaded(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));
    // // this->_DrawTriangleWireframe(Vec2(-70, -70), Vec2(70, -25), Vec2(80, 80), RGBA(255, 0, 0, 255));

    // The four "front" vertices
    shared_ptr<Vec3> v0 = make_shared<Vec3>(1, 1, 1);
    shared_ptr<Vec3> v1 = make_shared<Vec3>(-1, 1, 1);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(-1, -1, 1);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(1, -1, 1);
    // The four "back" vertices
    shared_ptr<Vec3> v4 = make_shared<Vec3>(1, 1, -1);
    shared_ptr<Vec3> v5 = make_shared<Vec3>(-1, 1, -1);
    shared_ptr<Vec3> v6 = make_shared<Vec3>(-1, -1, -1);
    shared_ptr<Vec3> v7 = make_shared<Vec3>(1, -1, -1);
    // the triangle mesh
    // front
    shared_ptr<Triangle> t0 = make_shared<Triangle>(v0, v1, v2);
    shared_ptr<Triangle> t1 = make_shared<Triangle>(v0, v2, v3);
    // right
    shared_ptr<Triangle> t2 = make_shared<Triangle>(v4, v0, v3);
    shared_ptr<Triangle> t3 = make_shared<Triangle>(v4, v3, v7);
    // back
    shared_ptr<Triangle> t4 = make_shared<Triangle>(v5, v4, v6);
    shared_ptr<Triangle> t5 = make_shared<Triangle>(v4, v7, v6);
    // left
    shared_ptr<Triangle> t6 = make_shared<Triangle>(v1, v5, v6);
    shared_ptr<Triangle> t7 = make_shared<Triangle>(v1, v6, v2);
    // top
    shared_ptr<Triangle> t8 = make_shared<Triangle>(v4, v5, v1);
    shared_ptr<Triangle> t9 = make_shared<Triangle>(v4, v1, v0);
    // down
    shared_ptr<Triangle> t10 = make_shared<Triangle>(v2, v6, v7);
    shared_ptr<Triangle> t11 = make_shared<Triangle>(v2, v7, v3);
    // the cube mesh
    shared_ptr<CubeMesh> c1 = make_shared<CubeMesh>(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
    // the cube instance
    this->_instances.push_back(Instance(c1, Transform(Vec3(0, 0, 5), Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 500, 0)));

    // lights
    this->_lights.push_back(make_shared<LightAmbient>(0.5));
    this->_lights.push_back(make_shared<LightPoint>(0.8, Vec3(2, 0, 4)));
    this->_lights.push_back(make_shared<LightDirectional>(2, Vec3(0, -1, 0)));

    this->Render();
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

void Rasterizer::_DrawLine(Vec3 from, Vec3 to, RGBA color, const Matrix &matrixProjection)
{
    // retrieve projected point
    unique_ptr<Vec> fromFactored = matrixProjection * VecHomogenous(from.x, from.y, from.z, 1);
    unique_ptr<Vec> toFactored = matrixProjection * VecHomogenous(to.x, to.y, to.z, 1);
    // cast to vec3
    Vec3 *fromProjected = dynamic_cast<Vec3 *>(fromFactored.get());
    Vec3 *toProjected = dynamic_cast<Vec3 *>(toFactored.get());
    // apply to vec2
    Vec2 fromVec2 = Vec2(fromProjected->x, fromProjected->y) * (1 / fromProjected->z);
    Vec2 toVec2 = Vec2(toProjected->x, toProjected->y) * (1 / toProjected->z);
    // interpolate zs for every sides
    vector<double> zFromTo;
    // InterpLinear(1 / v1.z, 1 / v2.z, xs12.size());
    // if line horizontal-ish
    if (abs(toVec2.x - fromVec2.x) > abs(toVec2.y - fromVec2.y))
    {
        if (fromVec2.x > toVec2.x)
        {
            swap(from, to);
            swap(fromVec2, toVec2);
        }
        // y = ax + b
        double a = (toVec2.y - fromVec2.y) / (toVec2.x - fromVec2.x);
        double y = fromVec2.y;
        zFromTo = InterpLinear(1 / from.z, 1 / to.z, toVec2.x - fromVec2.x);
        for (int x = fromVec2.x; x <= toVec2.x; x++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, zFromTo[x - fromVec2.x], color);
            // y(n+1) = y(n) + a
            y += a;
        }
    }
    // else line vertical-ish
    else
    {
        if (fromVec2.y > toVec2.y)
        {
            swap(from, to);
            swap(fromVec2, toVec2);
        }
        // x = ay + b
        double a = (toVec2.x - fromVec2.x) / (toVec2.y - fromVec2.y);
        double x = fromVec2.x;
        zFromTo = InterpLinear(1 / from.z, 1 / to.z, toVec2.y - fromVec2.y);
        for (int y = fromVec2.y; y <= toVec2.y; y++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, zFromTo[x - fromVec2.x], color);
            // x(n+1) = x(n) + a
            x += a;
        }
    }
}

void Rasterizer::_DrawTriangleWireframe(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const RGBA &color)
{
    this->_DrawLine(p1, p2, color);
    this->_DrawLine(p2, p3, color);
    this->_DrawLine(p3, p1, color);
}

void Rasterizer::_DrawTriangleWireframe(const Triangle &triangle, const RGBA &color, const Matrix &matrixProjection)
{
    array<shared_ptr<Vec3>, 3> vertices = triangle.GetVertices();
    Vec3 p1 = *vertices[0];
    Vec3 p2 = *vertices[1];
    Vec3 p3 = *vertices[2];
    this->_DrawLine(p1, p2, color, matrixProjection);
    this->_DrawLine(p2, p3, color, matrixProjection);
    this->_DrawLine(p3, p1, color, matrixProjection);
};

void Rasterizer::_DrawTriangleFilled(Vec2 p1, Vec2 p2, Vec2 p3, const RGBA &color)
{
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
    {
        std::swap(p1, p2);
    }
    if (p3.y < p1.y)
    {
        std::swap(p1, p3);
    }
    if (p3.y < p2.y)
    {
        std::swap(p2, p3);
    }
    // interpolate xs for every sides
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // merge small sides together for xs
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // find left and right side xs and zs
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
        // retrieve left, right side for xs
        int xLeft = xsLeft[y - p1.y];
        int xRight = xsRight[y - p1.y];
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            this->_canvas.SetPixelFromRGBA(x, y, color);
        }
    }
}

void Rasterizer::_DrawTriangleFilled(const Triangle &triangle, const Material &material, const Matrix &matrixProjection)
{
    array<shared_ptr<Vec3>, 3> vertices = triangle.GetVertices();
    Vec3 v1 = *vertices[0];
    Vec3 v2 = *vertices[1];
    Vec3 v3 = *vertices[2];
    // retrieve projected point
    Triangle projectedTriangle = triangle * matrixProjection;
    array<shared_ptr<Vec3>, 3> projectedVertices = projectedTriangle.GetVertices();
    vertices = projectedTriangle.GetVertices();
    // apply to vec2
    Vec2 p1 = Vec2(projectedVertices[0]->x, projectedVertices[0]->y) * (1 / projectedVertices[0]->z);
    Vec2 p2 = Vec2(projectedVertices[1]->x, projectedVertices[1]->y) * (1 / projectedVertices[1]->z);
    Vec2 p3 = Vec2(projectedVertices[2]->x, projectedVertices[2]->y) * (1 / projectedVertices[2]->z);
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
    {
        std::swap(p1, p2);
        std::swap(v1, v2);
    }
    if (p3.y < p1.y)
    {
        std::swap(p1, p3);
        std::swap(v1, v3);
    }
    if (p3.y < p2.y)
    {
        std::swap(p2, p3);
        std::swap(v2, v3);
    }
    // interpolate xs for every sides
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // interpolate zs for every sides
    vector<double> zs12 = InterpLinear(1 / v1.z, 1 / v2.z, xs12.size());
    vector<double> zs13 = InterpLinear(1 / v1.z, 1 / v3.z, xs13.size());
    vector<double> zs23 = InterpLinear(1 / v2.z, 1 / v3.z, xs23.size());
    // merge small sides together for xs
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // merge small sides together for zs
    vector<double> zs1223;
    zs1223.insert(zs1223.end(), zs12.begin(), zs12.end() - 1);
    zs1223.insert(zs1223.end(), zs23.begin(), zs23.end());
    // find left and right side xs and zs
    vector<double> xsLeft;
    vector<double> xsRight;
    vector<double> zsLeft;
    vector<double> zsRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        xsRight = xs1223;
        zsLeft = zs13;
        zsRight = zs1223;
    }
    else
    {
        xsLeft = xs1223;
        xsRight = xs13;
        zsLeft = zs1223;
        zsRight = zs13;
    }
    // get lighting coeff
    double lightingCoeff = this->_GetLightingCoeff(v1, triangle.GetNormal(), material);
    RGBA color = material.GetColor() * lightingCoeff;
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side for xs
        int xLeft = xsLeft[y - p1.y];
        int xRight = xsRight[y - p1.y];
        // retrieve left, right for zs
        double zLeft = zsLeft[y - p1.y];
        double zRight = zsRight[y - p1.y];
        // interpolate a z depth from left to right
        vector<double> zSegment = InterpLinear(zLeft, zRight, xRight - xLeft);
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            double z = zSegment[x - xLeft];
            this->_canvas.SetPixelFromRGBA(x, y, z, color);
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

void Rasterizer::_DrawTriangleShaded(const Triangle &triangle, const Material &material, const Matrix &matrixProjection)
{
    array<shared_ptr<Vec3>, 3> vertices = triangle.GetVertices();
    Vec3 v1 = *vertices[0];
    Vec3 v2 = *vertices[1];
    Vec3 v3 = *vertices[2];
    // retrieve projected point
    Triangle projectedTriangle = triangle * matrixProjection;
    array<shared_ptr<Vec3>, 3> projectedVertices = projectedTriangle.GetVertices();
    vertices = projectedTriangle.GetVertices();
    // apply to vec2
    Vec2 p1 = Vec2(projectedVertices[0]->x, projectedVertices[0]->y) * (1 / projectedVertices[0]->z);
    Vec2 p2 = Vec2(projectedVertices[1]->x, projectedVertices[1]->y) * (1 / projectedVertices[1]->z);
    Vec2 p3 = Vec2(projectedVertices[2]->x, projectedVertices[2]->y) * (1 / projectedVertices[2]->z);
    // put smallest y in p1 and biggest in p3
    if (p2.y < p1.y)
    {
        std::swap(p1, p2);
        std::swap(v1, v2);
    }
    if (p3.y < p1.y)
    {
        std::swap(p1, p3);
        std::swap(v1, v3);
    }
    if (p3.y < p2.y)
    {
        std::swap(p2, p3);
        std::swap(v2, v3);
    }
    // get lighting coeff
    double i1 = this->_GetLightingCoeff(v1, triangle.GetNormal(), material);
    double i2 = this->_GetLightingCoeff(v2, triangle.GetNormal(), material);
    double i3 = this->_GetLightingCoeff(v3, triangle.GetNormal(), material);
    // interpolate xs for every sides
    vector<double> xs12 = InterpLinear(p1.x, p2.x, p2.y - p1.y);
    vector<double> xs13 = InterpLinear(p1.x, p3.x, p3.y - p1.y);
    vector<double> xs23 = InterpLinear(p2.x, p3.x, p3.y - p2.y);
    // interpolate zs for every sides
    vector<double> zs12 = InterpLinear(1 / v1.z, 1 / v2.z, xs12.size());
    vector<double> zs13 = InterpLinear(1 / v1.z, 1 / v3.z, xs13.size());
    vector<double> zs23 = InterpLinear(1 / v2.z, 1 / v3.z, xs23.size());
    // interpolate intensity for every height
    vector<double> is12 = InterpLinear(i1, i2, xs12.size());
    vector<double> is13 = InterpLinear(i1, i3, xs13.size());
    vector<double> is23 = InterpLinear(i2, i3, xs23.size());
    // merge small sides together for xs
    vector<double> xs1223;
    xs1223.insert(xs1223.end(), xs12.begin(), xs12.end() - 1);
    xs1223.insert(xs1223.end(), xs23.begin(), xs23.end());
    // merge small sides together for zs
    vector<double> zs1223;
    zs1223.insert(zs1223.end(), zs12.begin(), zs12.end() - 1);
    zs1223.insert(zs1223.end(), zs23.begin(), zs23.end());
    // merge small sides together for is
    vector<double> is1223;
    is1223.insert(is1223.end(), is12.begin(), is12.end() - 1);
    is1223.insert(is1223.end(), is23.begin(), is23.end());
    // find left and right side xs and zs
    vector<double> xsLeft;
    vector<double> xsRight;
    vector<double> zsLeft;
    vector<double> zsRight;
    vector<double> isLeft;
    vector<double> isRight;
    int middle = std::floor(xs1223.size() / 2);
    if (xs13[middle] < xs1223[middle])
    {
        xsLeft = xs13;
        xsRight = xs1223;
        zsLeft = zs13;
        zsRight = zs1223;
        isLeft = is13;
        isRight = is1223;
    }
    else
    {
        xsLeft = xs1223;
        xsRight = xs13;
        zsLeft = zs1223;
        zsRight = zs13;
        isLeft = is1223;
        isRight = is13;
    }
    // for every y from bottom to top
    for (int y = p1.y; y < p3.y; y++)
    {
        // retrieve left, right side for xs
        int xLeft = xsLeft[y - p1.y];
        int xRight = xsRight[y - p1.y];
        // retrieve left, right for zs
        double zLeft = zsLeft[y - p1.y];
        double zRight = zsRight[y - p1.y];
        // retrieve insity left and right
        double iLeft = isLeft[y - p1.y];
        double iRight = isRight[y - p1.y];
        // interpolate a z depth from left to right
        vector<double> zSegment = InterpLinear(zLeft, zRight, xRight - xLeft);
        // interpolate intensity from left to right
        vector<double> is = InterpLinear(iLeft, iRight, xRight - xLeft);
        // draw a line from left to right
        for (int x = xLeft; x <= xRight; x++)
        {
            double z = zSegment[x - xLeft];
            RGBA color = material.GetColor() * is[x - xLeft];
            this->_canvas.SetPixelFromRGBA(x, y, z, color);
        }
    }
}

void Rasterizer::Render()
{
    this->_canvas.Reset();
    Matrix matrixCamera = this->_camera.GenerateMatrixCamera();
    vector<Instance> scenedInstances;
    for (auto instance : this->_instances)
    {
        scenedInstances.push_back(Instance(make_shared<CustomMesh>(instance.GetSceneTriangles(matrixCamera)), Transform(), instance.GetMaterial()));
    }
    vector<Instance> clippedInstances = ClipInstancesAgainstPlanes(scenedInstances, this->_camera.GetClippingPlanes());
    for (const Instance &instance : clippedInstances)
    {
        this->_RenderInstance(instance);
    }
};

void Rasterizer::_RenderInstance(const Instance &instance)
{
    for (auto triangle : instance.GetRawTriangles())
    {
        _RenderTriangle(*triangle, *instance.GetMaterial(), this->_matrixProjection);
    }
};

void Rasterizer::_RenderTriangle(const Triangle &triangle, const Material &material, const Matrix &matrixProjection)
{
    if (triangle.IsFacing(this->_camera.GetTransform().GetTranslation()))
    {
        array<shared_ptr<Vec3>, 3> vertices = triangle.GetVertices();
        // this->_DrawTriangleWireframe(triangle, RGBA(0, 0, 0, 255), matrixProjection);
        this->_DrawTriangleShaded(triangle, material, matrixProjection);
    }
}

double Rasterizer::_GetLightingCoeff(const Vec3 &position, const Vec3 &normal, const Material &material) const
{
    double coeff = 0;
    Vec3 direction = position - this->_camera.GetTransform().GetTranslation();
    for (auto light : this->_lights)
    {
        coeff += light->GetLightingCoeff(material, position, this->_camera.GetTransform().GetTranslation(), normal);
    }
    return coeff;
}

void Rasterizer::Input(bool forward, bool backward, bool left, bool right, bool up, bool down, double deltaTime)
{
    double x = (right ? 1 : 0) + (left ? -1 : 0);
    double y = (up ? 1 : 0) + (down ? -1 : 0);
    double z = (forward ? 1 : 0) + (backward ? -1 : 0);
    Vec3 translation = Vec3(x, y, z).Normalize();
    Transform cameraTransform = this->_camera.GetTransform();
    cameraTransform.SetTranslation(cameraTransform.GetTranslation() + (translation * deltaTime * 3.0));
    this->_camera.SetTransform(cameraTransform);
}

Matrix GenerateMatrixProjection(const Canvas &canvas, const Viewport &viewport)
{
    double widthRatio = (viewport.depth * (canvas.GetWidthMax() - 1)) / viewport.width;
    double heightRatio = (viewport.depth * (canvas.GetHeightMax() - 1)) / viewport.height;
    return Matrix({widthRatio, 0, 0, 0, 0, heightRatio, 0, 0, 0, 0, 1, 0}, 3, 4);
}

vector<Instance> ClipInstancesAgainstPlanes(const vector<Instance> &instances, const array<Plane, 5> &clipPlanes)
{
    vector<Instance> res;
    for (const Instance instance : instances)
    {
        optional<Instance> clippedInstance = ClipInstanceAgainstPlanes(instance, clipPlanes);
        if (clippedInstance.has_value())
        {
            res.push_back(clippedInstance.value());
        }
    }
    return res;
};

optional<Instance> ClipInstanceAgainstPlanes(Instance instance, const array<Plane, 5> &clipPlanes)
{
    for (const auto &clipPlane : clipPlanes)
    {
        optional<Instance> optInstance = ClipInstanceAgainstPlane(instance, clipPlane);
        if (!optInstance.has_value())
        {
            return {};
        }
        instance = optInstance.value();
    }
    return instance;
}

optional<Instance> ClipInstanceAgainstPlane(const Instance &instance, const Plane &clipPlane)
{
    Sphere boundingSphere = instance.GetBoundingSphere();
    double radius = boundingSphere.GetRadius();
    Vec3 center = boundingSphere.GetCenter();
    double signedDistance = clipPlane.SignedDist(center);
    if (signedDistance > radius)
    {
        return instance;
    }
    if (signedDistance < -radius)
    {
        return {};
    }
    vector<Triangle> triangles = ClipTrianglesAgainstPlane(instance.GetRawTriangles(), clipPlane);
    return Instance(make_shared<CustomMesh>(triangles), instance.GetTransform(), instance.GetMaterial());
}

vector<Triangle> ClipTrianglesAgainstPlane(const vector<shared_ptr<Triangle>> &triangles, const Plane &clipPlane)
{
    vector<Triangle> res;
    for (const auto &triangle : triangles)
    {
        vector<Triangle> clippedTriangles = ClipTriangleAgainstPlane(triangle, clipPlane);
        res.insert(res.end(), clippedTriangles.begin(), clippedTriangles.end());
    }
    return res;
};

vector<Triangle> ClipTriangleAgainstPlane(const shared_ptr<Triangle> &triangle, const Plane &clipPlane)
{
    vector<Triangle> res;

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
        res.push_back(*triangle);
        return res;
    }
    // if all distance negative
    if (d1 < 0 && d2 < 0 && d3 < 0)
    {
        return res;
    }
    // Some vertices inside, some outside
    vector<shared_ptr<Vec3>> insideVertices;
    vector<shared_ptr<Vec3>> outsideVertices;

    if (d1 >= 0)
        insideVertices.push_back(v1);
    else
        outsideVertices.push_back(v1);

    if (d2 >= 0)
        insideVertices.push_back(v2);
    else
        outsideVertices.push_back(v2);

    if (d3 >= 0)
        insideVertices.push_back(v3);
    else
        outsideVertices.push_back(v3);

    // Handle cases where one vertex is inside and two are outside
    if (insideVertices.size() == 1)
    {
        shared_ptr<Vec3> inside = insideVertices[0];
        shared_ptr<Vec3> outside1 = outsideVertices[0];
        shared_ptr<Vec3> outside2 = outsideVertices[1];

        Vec3 intersection1 = clipPlane.Intersection(*inside, *outside1 - *inside);
        Vec3 intersection2 = clipPlane.Intersection(*inside, *outside2 - *inside);

        res.push_back(Triangle(inside, make_shared<Vec3>(intersection1), make_shared<Vec3>(intersection2)));
    }

    // Handle cases where two vertices are inside and one is outside
    else if (insideVertices.size() == 2)
    {
        shared_ptr<Vec3> inside1 = insideVertices[0];
        shared_ptr<Vec3> inside2 = insideVertices[1];
        shared_ptr<Vec3> outside = outsideVertices[0];

        Vec3 intersection1 = clipPlane.Intersection(*inside1, *outside - *inside1);
        Vec3 intersection2 = clipPlane.Intersection(*inside2, *outside - *inside2);

        res.push_back(Triangle(inside1, inside2, make_shared<Vec3>(intersection1)));
        res.push_back(Triangle(inside2, make_shared<Vec3>(intersection1), make_shared<Vec3>(intersection2)));
    }

    return res;
}