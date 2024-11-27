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
