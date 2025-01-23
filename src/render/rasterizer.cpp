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
    // front
    shared_ptr<Triangle> t1 = make_shared<Triangle>(v5, v8, v7);
    shared_ptr<Triangle> t2 = make_shared<Triangle>(v7, v6, v5);
    // left
    shared_ptr<Triangle> t3 = make_shared<Triangle>(v7, v2, v6);
    shared_ptr<Triangle> t4 = make_shared<Triangle>(v7, v2, v3);
    // back
    shared_ptr<Triangle> t5 = make_shared<Triangle>(v1, v2, v4);
    shared_ptr<Triangle> t6 = make_shared<Triangle>(v2, v3, v4);
    // right
    shared_ptr<Triangle> t7 = make_shared<Triangle>(v4, v8, v5);
    shared_ptr<Triangle> t8 = make_shared<Triangle>(v5, v1, v4);
    // top
    shared_ptr<Triangle> t9 = make_shared<Triangle>(v5, v6, v2);
    shared_ptr<Triangle> t10 = make_shared<Triangle>(v2, v1, v5);
    // down
    shared_ptr<Triangle> t11 = make_shared<Triangle>(v4, v3, v7);
    shared_ptr<Triangle> t12 = make_shared<Triangle>(v7, v8, v4);
    // the cube mesh
    shared_ptr<CubeMesh> c1 = make_shared<CubeMesh>(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
    // the cube instance

    // this->_instances.push_back(Instance(c1, Transform(Vec3(-1.5, 0, 7), Rotation(0, 0, 0), Vec3(1, 1, 1))));
    this->_instances.push_back(Instance(c1, Transform(Vec3(0, 0, 3.5), Rotation(0, 20, 0), Vec3(1, 1, 1))));

    // lights
    this->_lights.push_back(make_shared<LightAmbient>(0.2));
    this->_lights.push_back(make_shared<LightPoint>(0.8, Vec3(2, 1, 0)));
    this->_lights.push_back(make_shared<LightDirectional>(0.2, Vec3(1.0, 4.0, 4.0)));

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

void Rasterizer::_DrawTriangleFilled(const Triangle &triangle, const RGBA &color, const Matrix &matrixProjection)
{
    array<shared_ptr<Vec3>, 3> vertices = triangle.GetVertices();
    Vec3 v1 = *vertices[0];
    Vec3 v2 = *vertices[1];
    Vec3 v3 = *vertices[2];
    // retrieve projected point
    unique_ptr<Vec> p1Factored = matrixProjection * VecHomogenous(v1.x, v1.y, v1.z, 1);
    unique_ptr<Vec> p2Factored = matrixProjection * VecHomogenous(v2.x, v2.y, v2.z, 1);
    unique_ptr<Vec> p3Factored = matrixProjection * VecHomogenous(v3.x, v3.y, v3.z, 1);
    // cast to vec3
    Vec3 *p1Vec3 = dynamic_cast<Vec3 *>(p1Factored.get());
    Vec3 *p2Vec3 = dynamic_cast<Vec3 *>(p2Factored.get());
    Vec3 *p3Vec3 = dynamic_cast<Vec3 *>(p3Factored.get());
    // apply to vec2
    Vec2 p1 = Vec2(p1Vec3->x, p1Vec3->y) * (1 / p1Vec3->z);
    Vec2 p2 = Vec2(p2Vec3->x, p2Vec3->y) * (1 / p2Vec3->z);
    Vec2 p3 = Vec2(p3Vec3->x, p3Vec3->y) * (1 / p3Vec3->z);
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
    double lightingCoeff = this->_GetLightingCoeff(triangle);
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
            this->_canvas.SetPixelFromRGBA(x, y, z, color * lightingCoeff);
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
    Matrix matrixInstance = instance.GenerateMatrixInstance();
    vector<shared_ptr<Triangle>> triangles = instance.GetMesh()->GetTriangles();
    for (auto triangle : triangles)
    {
        _RenderTriangle(*triangle, matrixCamera, matrixInstance, this->_matrixProjection);
    }
};

void Rasterizer::_RenderTriangle(const Triangle &triangle, const Matrix &matrixCamera, const Matrix &matrixInstance, const Matrix &matrixProjection)
{
    Triangle matrixedTriangle = triangle.Matrixed(matrixCamera, matrixInstance);
    if (matrixedTriangle.IsFacing(this->_camera.GetTransform().GetTranslation()))
    {
        this->_DrawTriangleFilled(matrixedTriangle, RGBA(0, 255, 0, 255), matrixProjection);
        this->_DrawTriangleWireframe(matrixedTriangle, RGBA(0, 0, 0, 255), matrixProjection);
    }
}

double Rasterizer::_GetLightingCoeff(const Triangle &triangle) const
{
    double coeff = 0;
    Vec3 position = *triangle.GetVertices()[0];
    Vec3 normal = triangle.GetNormal();
    Vec3 direction = position - this->_camera.GetTransform().GetTranslation();
    for (auto light : this->_lights)
    {
        coeff += light->Diffuse(direction, position, normal);
    }
    return coeff;
}

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
        optional<Instance> optInstance = ClipInstanceAgainstPlane(res, clipPlane);
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
    Sphere boundingSphere = instance.GetBoundingSphere();
    double radius = boundingSphere.GetRadius();
    Vec3 center = boundingSphere.GetCenter();
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
        Vec3 positive1 = clipPlane.Intersection(*positive, (*negative1 - *positive));
        Vec3 positive2 = clipPlane.Intersection(*positive, (*negative2 - *positive));
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
        Vec3 npositive1 = clipPlane.Intersection(*positive1, (*negative - *positive1));
        Vec3 npositive2 = clipPlane.Intersection(*positive2, (*negative - *positive2));
        shared_ptr<Vec3> ptr_npositive1 = make_shared<Vec3>(npositive1.x, npositive1.y, npositive1.z);
        res.push_back(make_shared<Triangle>(positive1, positive2, ptr_npositive1));
        res.push_back(make_shared<Triangle>(ptr_npositive1, positive2, make_shared<Vec3>(npositive2.x, npositive2.y, npositive2.z)));
    }
    return res;
}