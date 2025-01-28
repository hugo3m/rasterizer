#include <gtest/gtest.h>
#include "../src/math/matrix.hpp"

TEST(Matrix, Instanciate)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[0][2], 3);
    EXPECT_EQ(matrix[1][0], 4);
    EXPECT_EQ(matrix[1][1], 5);
    EXPECT_EQ(matrix[1][2], 6);
}

TEST(Matrix, Instanciate2)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    EXPECT_EQ(matrix.Get(0, 0), 1);
    EXPECT_EQ(matrix.Get(0, 1), 2);
    EXPECT_EQ(matrix.Get(0, 2), 3);
    EXPECT_EQ(matrix.Get(1, 0), 4);
    EXPECT_EQ(matrix.Get(1, 1), 5);
    EXPECT_EQ(matrix.Get(1, 2), 6);
}

TEST(Matrix, Instanciate3)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    EXPECT_EQ(matrix.Get(0, 0), matrix[0][0]);
    EXPECT_EQ(matrix.Get(0, 1), matrix[0][1]);
    EXPECT_EQ(matrix.Get(0, 2), matrix[0][2]);
    EXPECT_EQ(matrix.Get(1, 0), matrix[1][0]);
    EXPECT_EQ(matrix.Get(1, 1), matrix[1][1]);
    EXPECT_EQ(matrix.Get(1, 2), matrix[1][2]);
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

TEST(Matrix, OperatorMulMatrix2)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);
    Matrix init = Matrix({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 4, 4);
    Matrix res = matrix * init;
    EXPECT_EQ(res[0][0], init[0][0]);
    EXPECT_EQ(res[0][1], init[0][1]);
    EXPECT_EQ(res[1][0], init[1][0]);
    EXPECT_EQ(res[1][1], init[1][1]);
    EXPECT_EQ(res[0][2], init[0][2]);
    EXPECT_EQ(res[0][3], init[0][3]);
    EXPECT_EQ(res[1][2], init[1][2]);
    EXPECT_EQ(res[1][3], init[1][3]);
    EXPECT_EQ(res[2][0], init[2][0]);
    EXPECT_EQ(res[2][1], init[2][1]);
    EXPECT_EQ(res[3][0], init[3][0]);
    EXPECT_EQ(res[3][1], init[3][1]);
    EXPECT_EQ(res[2][2], init[2][2]);
    EXPECT_EQ(res[2][3], init[2][3]);
    EXPECT_EQ(res[3][2], init[3][2]);
    EXPECT_EQ(res[3][3], init[3][3]);
}

TEST(Matrix, OperatorMulVec2)
{
    Matrix matrix = Matrix({1, 0, 0, 1}, 2, 2);
    Vec2 init = Vec2(4, 5);
    unique_ptr<Vec> vecres = matrix * init;
    Vec2 *pres = dynamic_cast<Vec2 *>(vecres.get());
    EXPECT_NE(pres, nullptr);
    if (pres)
    {
        Vec2 res = *pres;
        EXPECT_EQ(res.x, init.x);
        EXPECT_EQ(res.y, init.y);
    }
}

TEST(Matrix, OperatorMulVec3)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3);
    Vec3 init = Vec3(4, 5, 75);
    unique_ptr<Vec> vecres = matrix * init;
    Vec3 *pres = dynamic_cast<Vec3 *>(vecres.get());
    EXPECT_NE(pres, nullptr);
    if (pres)
    {
        EXPECT_EQ(pres->x, init.x);
        EXPECT_EQ(pres->y, init.y);
        EXPECT_EQ(pres->z, init.z);
    }
}

TEST(Matrix, OperatorMulVecHomogenous)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);
    VecHomogenous init = VecHomogenous(4, 5, 75, -85);
    unique_ptr<Vec> vecres = matrix * init;
    VecHomogenous *pres = dynamic_cast<VecHomogenous *>(vecres.get());
    EXPECT_NE(pres, nullptr);
    if (pres)
    {
        VecHomogenous res = *pres;
        EXPECT_EQ(res.x, init.x);
        EXPECT_EQ(res.y, init.y);
        EXPECT_EQ(res.z, init.z);
        EXPECT_EQ(res.w, init.w);
    }
}

TEST(Matrix, Minor)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    Matrix res = matrix.Minor(0, 0);
    EXPECT_EQ(res.GetColumnLength(), 2);
    EXPECT_EQ(res.GetRowLength(), 2);
    EXPECT_EQ(res[0][0], 5);
    EXPECT_EQ(res[0][1], 6);
    EXPECT_EQ(res[1][0], 8);
    EXPECT_EQ(res[1][1], 9);
}

TEST(Matrix, Determinant22)
{
    Matrix matrix = Matrix({3, 8, 4, 6}, 2, 2);
    EXPECT_EQ(matrix.Determinant(), -14);
}

TEST(Matrix, Determinant44)
{
    Matrix matrix = Matrix({5, 8, -6, 6, 2, -8, 1, 3, -5, 5, 2, -1, 3, 9, 7, -4}, 4, 4);
    EXPECT_EQ(matrix.Determinant(), 3766);
}

TEST(Matrix, Determinant442)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);
    EXPECT_EQ(matrix.Determinant(), 1);
}

TEST(Matrix, Comatrice)
{
    Matrix matrix = Matrix({1, 2, 3, 0, 1, 2, -1, -4, -1}, 3, 3);
    Matrix cofactor = matrix.Cofactor();
    Matrix expect = Matrix({7, -2, 1, -10, 2, 2, 1, -2, 1}, 3, 3);
    EXPECT_EQ(cofactor[0][0], expect[0][0]);
    EXPECT_EQ(cofactor[0][1], expect[0][1]);
    EXPECT_EQ(cofactor[0][2], expect[0][2]);
    EXPECT_EQ(cofactor[1][0], expect[1][0]);
    EXPECT_EQ(cofactor[1][1], expect[1][1]);
    EXPECT_EQ(cofactor[1][2], expect[1][2]);
    EXPECT_EQ(cofactor[2][0], expect[2][0]);
    EXPECT_EQ(cofactor[2][1], expect[2][1]);
    EXPECT_EQ(cofactor[2][2], expect[2][2]);
}

TEST(Matrix, Comatrice2)
{
    Matrix matrix = Matrix({1, 0, 2, 0, 0, 3, 0, 4, 5, 0, 6, 0, 0, 7, 0, 8}, 4, 4);
    Matrix cofactor = matrix.Cofactor();
    Matrix expect = Matrix({-24, 0, 20, 0, 0, -32, 0, 28, 8, 0, -4, 0, 0, 16, 0, -12}, 4, 4);
    EXPECT_EQ(cofactor[0][0], expect[0][0]);
    EXPECT_EQ(cofactor[0][1], expect[0][1]);
    EXPECT_EQ(cofactor[0][2], expect[0][2]);
    EXPECT_EQ(cofactor[0][3], expect[0][3]);
    EXPECT_EQ(cofactor[1][0], expect[1][0]);
    EXPECT_EQ(cofactor[1][1], expect[1][1]);
    EXPECT_EQ(cofactor[1][2], expect[1][2]);
    EXPECT_EQ(cofactor[1][3], expect[1][3]);
    EXPECT_EQ(cofactor[2][0], expect[2][0]);
    EXPECT_EQ(cofactor[2][1], expect[2][1]);
    EXPECT_EQ(cofactor[2][2], expect[2][2]);
    EXPECT_EQ(cofactor[2][3], expect[2][3]);
    EXPECT_EQ(cofactor[3][0], expect[3][0]);
    EXPECT_EQ(cofactor[3][1], expect[3][1]);
    EXPECT_EQ(cofactor[3][2], expect[3][2]);
    EXPECT_EQ(cofactor[3][3], expect[3][3]);
}

TEST(Matrix, Transpose)
{
    Matrix matrix = Matrix({7, -2, 1, -10, 2, 2, 1, -2, 1}, 3, 3);
    Matrix transpose = matrix.Transpose();
    Matrix expect = Matrix({7, -10, 1, -2, 2, -2, 1, 2, 1}, 3, 3);
    EXPECT_EQ(transpose[0][0], expect[0][0]);
    EXPECT_EQ(transpose[0][1], expect[0][1]);
    EXPECT_EQ(transpose[0][2], expect[0][2]);
    EXPECT_EQ(transpose[1][0], expect[1][0]);
    EXPECT_EQ(transpose[1][1], expect[1][1]);
    EXPECT_EQ(transpose[1][2], expect[1][2]);
    EXPECT_EQ(transpose[2][0], expect[2][0]);
    EXPECT_EQ(transpose[2][1], expect[2][1]);
    EXPECT_EQ(transpose[2][2], expect[2][2]);
}

TEST(Matrix, MatrixMatrix)
{
    Matrix matrix = Matrix({1, 2, 3, 4}, 2, 2);
    Matrix res = Matrix(matrix);
    EXPECT_EQ(res[0][0], matrix[0][0]);
    EXPECT_EQ(res[1][0], matrix[1][0]);
    EXPECT_EQ(res[0][1], matrix[0][1]);
    EXPECT_EQ(res[1][1], matrix[1][1]);
}

TEST(Matrix, OperatorMulDouble)
{
    Matrix matrix = Matrix({1, 2, 3, 4}, 2, 2);
    const double fact = 2;
    Matrix res = matrix * fact;
    EXPECT_EQ(res[0][0], 2);
    EXPECT_EQ(res[0][1], 4);
    EXPECT_EQ(res[1][0], 6);
    EXPECT_EQ(res[1][1], 8);
}

TEST(Matrix, Adjoint)
{
    Matrix matrix = Matrix({1, 2, -1, 2, 1, 2, -1, 2, 1}, 3, 3);
    Matrix adjoint = matrix.Adjoint();
    EXPECT_EQ(adjoint[0][0], -3);
    EXPECT_EQ(adjoint[0][1], -4);
    EXPECT_EQ(adjoint[0][2], 5);
    EXPECT_EQ(adjoint[1][0], -4);
    EXPECT_EQ(adjoint[1][1], 0);
    EXPECT_EQ(adjoint[1][2], -4);
    EXPECT_EQ(adjoint[2][0], 5);
    EXPECT_EQ(adjoint[2][1], -4);
    EXPECT_EQ(adjoint[2][2], -3);
}

TEST(Matrix, Adjoint2)
{
    Matrix matrix = Matrix({1, 2, 3, 4, 5, -5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 4, 4);
    Matrix adjoint = matrix.Adjoint();
    EXPECT_EQ(adjoint[0][0], 44);
    EXPECT_EQ(adjoint[0][1], 0);
    EXPECT_EQ(adjoint[0][2], -132);
    EXPECT_EQ(adjoint[0][3], 88);
    EXPECT_EQ(adjoint[1][0], 0);
    EXPECT_EQ(adjoint[1][1], 0);
    EXPECT_EQ(adjoint[1][2], 0);
    EXPECT_EQ(adjoint[1][3], 0);
    EXPECT_EQ(adjoint[2][0], -132);
    EXPECT_EQ(adjoint[2][1], 0);
    EXPECT_EQ(adjoint[2][2], 396);
    EXPECT_EQ(adjoint[2][3], -264);
    EXPECT_EQ(adjoint[3][0], 88);
    EXPECT_EQ(adjoint[3][1], 0);
    EXPECT_EQ(adjoint[3][2], -264);
    EXPECT_EQ(adjoint[3][3], 176);
}

TEST(Matrix, Inverse)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3);
    Matrix inverse = matrix.Inverse();
    EXPECT_EQ(inverse[0][0], 1);
    EXPECT_EQ(inverse[0][1], 0);
    EXPECT_EQ(inverse[0][2], 0);
    EXPECT_EQ(inverse[1][0], 0);
    EXPECT_EQ(inverse[1][1], 1);
    EXPECT_EQ(inverse[1][2], 0);
    EXPECT_EQ(inverse[2][0], 0);
    EXPECT_EQ(inverse[2][1], 0);
    EXPECT_EQ(inverse[2][2], 1);
}

TEST(Matrix, Inverse2)
{
    Matrix matrix = Matrix({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 4, 4);
    Matrix inverse = matrix.Inverse();
    EXPECT_EQ(inverse[0][0], 1);
    EXPECT_EQ(inverse[0][1], 0);
    EXPECT_EQ(inverse[0][2], 0);
    EXPECT_EQ(inverse[0][3], 0);
    EXPECT_EQ(inverse[1][0], 0);
    EXPECT_EQ(inverse[1][1], 1);
    EXPECT_EQ(inverse[1][2], 0);
    EXPECT_EQ(inverse[1][3], 0);
    EXPECT_EQ(inverse[2][0], 0);
    EXPECT_EQ(inverse[2][1], 0);
    EXPECT_EQ(inverse[2][2], 1);
    EXPECT_EQ(inverse[2][3], 0);
    EXPECT_EQ(inverse[3][0], 0);
    EXPECT_EQ(inverse[3][1], 0);
    EXPECT_EQ(inverse[3][2], 0);
    EXPECT_EQ(inverse[3][3], 1);
}
