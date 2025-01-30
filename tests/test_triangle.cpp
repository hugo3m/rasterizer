#include <gtest/gtest.h>
#include "../src/math/triangle.hpp"

TEST(TriangleTest, HasIntersection)
{
    Triangle triangle = Triangle(make_shared<Vec3>(1, 1, 0), make_shared<Vec3>(2, 1, 0), make_shared<Vec3>(2, 2, 0));
    EXPECT_TRUE(triangle.HasIntersection(Vec3(1.5, 1.5, -1), Vec3(0, 0, 1)));
    EXPECT_FALSE(triangle.HasIntersection(Vec3(1.5, 1.5, -1), Vec3(0, 0, -1)));
}

TEST(TriangleTest, IsFacing)
{
    Triangle triangle = Triangle(make_shared<Vec3>(0, 0, 0), make_shared<Vec3>(1, 0, 0), make_shared<Vec3>(0, 1, 0));
    EXPECT_FALSE(triangle.IsFacing(Vec3(0, 0, -1)));
    EXPECT_TRUE(triangle.IsFacing(Vec3(0, 0, 1)));
}

TEST(TriangleTest, IsFacing2)
{
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
    shared_ptr<Triangle> t5 = make_shared<Triangle>(v5, v7, v6);
    // left
    shared_ptr<Triangle> t6 = make_shared<Triangle>(v1, v5, v6);
    shared_ptr<Triangle> t7 = make_shared<Triangle>(v1, v6, v2);
    // top
    shared_ptr<Triangle> t8 = make_shared<Triangle>(v4, v5, v1);
    shared_ptr<Triangle> t9 = make_shared<Triangle>(v4, v1, v0);
    // down
    shared_ptr<Triangle> t10 = make_shared<Triangle>(v2, v6, v7);
    shared_ptr<Triangle> t11 = make_shared<Triangle>(v2, v7, v3);

    Vec3 cameraPosition = Vec3(0, 0, -5);

    EXPECT_FALSE(t1->IsFacing(cameraPosition));
    EXPECT_FALSE(t2->IsFacing(cameraPosition));
    EXPECT_TRUE(t4->IsFacing(cameraPosition));
    EXPECT_TRUE(t5->IsFacing(cameraPosition));
}

TEST(TriangleTest, OperatorEqual)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);
    shared_ptr<Vec3> v4 = make_shared<Vec3>(0, 0, 1);

    Triangle t1 = Triangle(v1, v2, v3);
    Triangle t2 = Triangle(v1, v2, v4);
    Triangle t3 = Triangle(v2, v1, v3);

    EXPECT_TRUE(t1 == t3);
    EXPECT_FALSE(t2 == t1);
    EXPECT_FALSE(t3 == t2);
    EXPECT_TRUE(t3 == t1);
}

TEST(TriangleTest, OperatorEqual2)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);

    Triangle t1 = Triangle(v1, v2, v3);
    Triangle t3 = Triangle(v1, v2, v2);

    EXPECT_FALSE(t1 == t3);
    EXPECT_FALSE(t3 == t1);
}

TEST(TriangleTest, OperatorMul)
{
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);

    Triangle t = Triangle(v1, v2, v3);

    Matrix identity = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);

    Triangle it = t * identity;

    EXPECT_TRUE(t == it);
}