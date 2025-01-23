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