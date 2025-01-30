#include <gtest/gtest.h>
#include "../src/math/vec.hpp"

// Demonstrate some basic assertions.
TEST(VecTest, New)
{
    double A = 1;
    Vec3 vec = Vec3(A, A + 1, A + 2);
}

TEST(Vec3, Norm1)
{
    Vec3 vec = Vec3(0, 1, 0);
    EXPECT_EQ(vec.Norm(), 1);
}

TEST(Vec3, Norm2)
{
    Vec3 vec = Vec3(1, 1, 1);
    EXPECT_EQ(vec.Norm(), sqrt(3));
}

TEST(Vec3, Normalize1)
{
    Vec3 vec = Vec3(1, 0, 0);
    Vec3 normalize = vec.Normalize();
    EXPECT_EQ(normalize.x, 1);
    EXPECT_EQ(normalize.y, 0);
    EXPECT_EQ(normalize.z, 0);
}

TEST(Vec3, Normalize2)
{
    Vec3 vec = Vec3(1, 1, 1);
    Vec3 normalize = vec.Normalize();
    EXPECT_EQ(normalize.x, 1 / sqrt(3));
    EXPECT_EQ(normalize.y, 1 / sqrt(3));
    EXPECT_EQ(normalize.z, 1 / sqrt(3));
}

TEST(Vec3, Dot)
{
    Vec3 x = Vec3(1, 0, 0);
    Vec3 y = Vec3(0, 1, 0);
    Vec3 z = Vec3(0, 0, 1);
    EXPECT_EQ(x.Dot(y), 0);
    EXPECT_EQ(x.Dot(z), 0);
    EXPECT_EQ(y.Dot(z), 0);
}

TEST(Vec3, CrossProduct)
{
    Vec3 x = Vec3(1, 0, 0);
    Vec3 y = Vec3(0, 1, 0);
    Vec3 z = Vec3(0, 0, 1);
    EXPECT_TRUE(x.CrossProduct(y) == z);
    EXPECT_TRUE(y.CrossProduct(x) == (z * -1));
}

TEST(Vec3, Reflection)
{
    Vec3 norm = Vec3(0, -1, 0);
    Vec3 direction = Vec3(1, 1, 0);
    Vec3 reflected = Reflection(direction, norm);
    EXPECT_TRUE(reflected == Vec3(1, -1, 0));
}
