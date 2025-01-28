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
    Triangle triangle = Triangle(make_shared<Vec3>(1, 1, 0), make_shared<Vec3>(2, 1, 0), make_shared<Vec3>(2, 2, 0));
    EXPECT_TRUE(triangle.IsFacing(Vec3(1.5, 1.5, -1)));
    EXPECT_FALSE(triangle.IsFacing(Vec3(1.5, 1.5, 1)));
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