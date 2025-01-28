#include <gtest/gtest.h>
#include "../src/render/rasterizer.hpp"
#include "../src/meshes/triangle.hpp"

TEST(RasterizerTest, ClipTriangleAgainstPlane1)
{
    shared_ptr<Vec3> p1 = make_shared<Vec3>(1, 0, 1);
    shared_ptr<Vec3> n2 = make_shared<Vec3>(-1, 0, -1);
    shared_ptr<Vec3> n3 = make_shared<Vec3>(1, 0, -1);

    shared_ptr<Triangle> triangle = make_shared<Triangle>(p1, n2, n3);
    Plane plane = Plane(Vec3(0, 0, 1), 0);

    vector<Triangle> clippedTriangles = ClipTriangleAgainstPlane(triangle, plane);

    EXPECT_EQ(clippedTriangles.size(), 1);

    shared_ptr<Vec3> p2 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> p3 = make_shared<Vec3>(1, 0, 0);

    Triangle final = Triangle(p1, p2, p3);

    EXPECT_TRUE(clippedTriangles[0] == final);
}

TEST(RasterizerTest, ClipTriangleAgainstPlane2)
{
    shared_ptr<Vec3> p1 = make_shared<Vec3>(1, 0, 1);
    shared_ptr<Vec3> p2 = make_shared<Vec3>(-1, 0, 1);
    shared_ptr<Vec3> n1 = make_shared<Vec3>(1, 0, -1);

    shared_ptr<Triangle> triangle = make_shared<Triangle>(p1, p2, n1);
    Plane plane = Plane(Vec3(0, 0, 1), 0);

    vector<Triangle> clippedTriangles = ClipTriangleAgainstPlane(triangle, plane);

    EXPECT_EQ(clippedTriangles.size(), 2);

    shared_ptr<Vec3> np1 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> np2 = make_shared<Vec3>(0, 0, 0);

    // group 1
    Triangle t1 = Triangle(p1, p2, np1);
    Triangle t2 = Triangle(np1, p2, np2);

    EXPECT_TRUE(clippedTriangles[0] == t1);
    EXPECT_TRUE(clippedTriangles[1] == t2);
}

TEST(RasterizerTest, ClipInstanceAgainstPlanes1)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 1);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(-2, 0, 1);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 0, -1);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> triangle = make_shared<TriangleMesh>(t1);

    Instance instance = Instance(triangle, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Plane p1 = Plane(Vec3(1, 0, 0), -1);
    Plane p2 = Plane(Vec3(-1, 0, 0), -1);
    Plane p3 = Plane(Vec3(-1, 0, 0), -2);
    Plane p4 = Plane(Vec3(-1, 0, 0), -3);
    Plane p5 = Plane(Vec3(-1, 0, 0), -4);

    array<Plane, 5> planes = {p1, p2, p3, p4, p5};

    optional<Instance> clippedInstance = ClipInstanceAgainstPlanes(instance, planes);

    EXPECT_TRUE(clippedInstance.has_value());

    Instance inst = clippedInstance.value();

    EXPECT_EQ(inst.GetRawTriangles().size(), 2);
}

TEST(RasterizerTest, ClipInstanceAgainstPlanes2)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(-1, 0, 1);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(-3, 0, 1);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(-1, 0, -1);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> triangle = make_shared<TriangleMesh>(t1);

    Instance instance = Instance(triangle, Transform(Vec3(-2, 0, 0), Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Plane p1 = Plane(Vec3(1, 0, 0), -1);
    Plane p2 = Plane(Vec3(-1, 0, 0), -1);
    Plane p3 = Plane(Vec3(-1, 0, 0), -2);
    Plane p4 = Plane(Vec3(-1, 0, 0), -3);
    Plane p5 = Plane(Vec3(-1, 0, 0), -4);

    array<Plane, 5> planes = {p1, p2, p3, p4, p5};

    optional<Instance> clippedInstance = ClipInstanceAgainstPlanes(instance, planes);

    EXPECT_FALSE(clippedInstance.has_value());
}

TEST(RasterizerTest, ClipInstanceAgainstPlanes3)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 1);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(-2, 0, 1);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 0, -1);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> triangle = make_shared<TriangleMesh>(t1);

    Instance instance = Instance(triangle, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Plane p1 = Plane(Vec3(1, 0, 0), -1);
    Plane p2 = Plane(Vec3(-1, 0, 0), -1);
    Plane p3 = Plane(Vec3(-1, 0, 0), -2);
    Plane p4 = Plane(Vec3(-1, 0, 0), -3);
    Plane p5 = Plane(Vec3(0, 0, -1), -4);

    array<Plane, 5> planes = {p1, p2, p3, p4, p5};

    optional<Instance> clippedInstance = ClipInstanceAgainstPlanes(instance, planes);

    EXPECT_TRUE(clippedInstance.has_value());

    Instance inst = clippedInstance.value();

    EXPECT_EQ(inst.GetRawTriangles().size(), 2);
}