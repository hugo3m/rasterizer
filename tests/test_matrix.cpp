#include <gtest/gtest.h>
#include "../src/math/matrix.hpp"

TEST(Matrix, Instanciate)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[0][2], 3);
    EXPECT_EQ(matrix[1][0], 4);
    EXPECT_EQ(matrix[1][2], 6);
}

TEST(Matrix, InstanciateException)
{
    EXPECT_ANY_THROW(Matrix({1, 2, 3, 4, 5, 6}, 1, 1));
}

TEST(Matrix, OperatorMulMatrix)
{
    Matrix matrix = Matrix({1, 0, 0, 1}, 2, 2);
    Matrix init = Matrix({1, 2, 3, 4}, 2, 2);
    Matrix res = matrix * init;
    EXPECT_EQ(res[0][0], init[0][0]);
    EXPECT_EQ(res[0][1], init[0][1]);
    EXPECT_EQ(res[1][0], init[1][0]);
    EXPECT_EQ(res[1][1], init[1][1]);
}

TEST(Matrix, OperatorMulVec2)
{
    Matrix matrix = Matrix({1, 0, 0, 1}, 2, 2);
    Vec2 init = Vec2(4, 5);
    Vec2 res = matrix * init;
    EXPECT_EQ(res.x, init.x);
    EXPECT_EQ(res.y, init.y);
}

TEST(Matrix, OperatorMulVec3)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3);
    Vec3 init = Vec3(4, 5, 75);
    Vec3 res = matrix * init;
    EXPECT_EQ(res.x, init.x);
    EXPECT_EQ(res.y, init.y);
    EXPECT_EQ(res.z, init.z);
}

TEST(Matrix, OperatorMulVecHomogenous)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);
    VecHomogenous init = VecHomogenous(4, 5, 75, -85);
    VecHomogenous res = matrix * init;
    EXPECT_EQ(res.x, init.x);
    EXPECT_EQ(res.y, init.y);
    EXPECT_EQ(res.z, init.z);
    EXPECT_EQ(res.w, init.w);
}
