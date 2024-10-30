#include <gtest/gtest.h>
#include "../src/math/vec.hpp"

// Demonstrate some basic assertions.
TEST(VecTest, New)
{
    double A = 1;
    Vec3 vec = Vec3(A, A + 1, A + 2);
}