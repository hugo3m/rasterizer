#include <gtest/gtest.h>
#include "math.h"
#include "../src/meshes/cube.hpp"
#include "../src/meshes/triangle.hpp"
#include "../src/instances/instance.hpp"
#include "../src/instances/camera.hpp"

TEST(InstanceTest, GetBoundingCirlce)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);
    shared_ptr<Vec3> v4 = make_shared<Vec3>(1, 1, 0);
    // The four "back" vertices
    shared_ptr<Vec3> v5 = make_shared<Vec3>(0, 0, 1);
    shared_ptr<Vec3> v6 = make_shared<Vec3>(1, 0, 1);
    shared_ptr<Vec3> v7 = make_shared<Vec3>(0, 1, 1);
    shared_ptr<Vec3> v8 = make_shared<Vec3>(1, 1, 1);
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

    Vec3 translation(1.5, 0, 5);
    Instance instance(c1, Transform(translation, Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Sphere boundingSphere = instance.GetBoundingSphere();
    EXPECT_TRUE(boundingSphere.GetCenter() == (Vec3(0.5, 0.5, 0.5) + translation));
    EXPECT_EQ(boundingSphere.GetRadius(), Vec3(0.5, 0.5, 0.5).Norm());
}

TEST(InstanceTest, GenerateMatrixInstance1)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> c1 = make_shared<TriangleMesh>(t1);

    Vec3 translation(0, 0, 0);
    Instance instance(c1, Transform(translation, Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Matrix m = instance.GenerateMatrixInstance();

    Triangle it = (*t1) * m;

    EXPECT_TRUE(it == *t1);
}

TEST(InstanceTest, GenerateMatrixInstance2)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> c1 = make_shared<TriangleMesh>(t1);

    Vec3 translation(10, -10, 2);
    Instance instance(c1, Transform(translation, Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Matrix m = instance.GenerateMatrixInstance();

    Triangle it = (*t1) * m;

    Triangle it2 = Triangle(make_shared<Vec3>(v1->x + translation.x, v1->y + translation.y, v1->z + translation.z), make_shared<Vec3>(v2->x + translation.x, v2->y + translation.y, v2->z + translation.z), make_shared<Vec3>(v3->x + translation.x, v3->y + translation.y, v3->z + translation.z));

    EXPECT_TRUE(it == it2);
}

TEST(InstanceTest, GetSceneTriangles)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> c1 = make_shared<TriangleMesh>(t1);

    Vec3 translation(0, 0, 0);
    Instance instance(c1, Transform(translation, Rotation(0, 0, 0), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Camera camera({1, 1, 1}, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(0, 0, 0)));

    vector<shared_ptr<Triangle>> sceneTriangles = instance.GetSceneTriangles(camera.GenerateMatrixCamera());

    EXPECT_EQ(sceneTriangles.size(), 1);

    EXPECT_TRUE((*sceneTriangles[0]) == (*t1));
}

TEST(InstanceTest, GetSceneTriangles2)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);
    shared_ptr<Vec3> v4 = make_shared<Vec3>(1, 1, 0);

    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);

    shared_ptr<TriangleMesh> c1 = make_shared<TriangleMesh>(t1);

    double radian = 90 * M_PI / 180.0;

    Vec3 translation(0, 0, 0);
    Instance instance(c1, Transform(translation, Rotation(0, 0, radian), Vec3(1, 1, 1)), make_shared<Material>(RGBA(0, 255, 0, 255), 0, 0));

    Camera camera({1, 1, 1}, Transform(Vec3(0, 0, 0), Rotation(0, 0, 0), Vec3(0, 0, 0)));

    vector<shared_ptr<Triangle>> sceneTriangles = instance.GetSceneTriangles(camera.GenerateMatrixCamera());

    EXPECT_EQ(sceneTriangles.size(), 1);

    shared_ptr<Triangle> t2 = make_shared<Triangle>(v1, v2, v4);

    EXPECT_TRUE((*sceneTriangles[0]) == (*t2));
}