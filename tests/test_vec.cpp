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
