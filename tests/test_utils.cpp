#include <gtest/gtest.h>
#include "../src/math/utils.hpp"

TEST(Utils, Interpolate1)
{
    vector<double> res = Interpolate(0, 0, 1, 10);
    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 10);
}

TEST(Utils, Interpolate2)
{
    vector<double> res = Interpolate(0, 0, 10, 10);
    EXPECT_EQ(res.size(), 11);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[10], 10);
}

TEST(Utils, Interpolate3)
{
    vector<double> res = Interpolate(0, 0, 3, -10);
    EXPECT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[3], -10);
}

TEST(Utils, Interpolate4)
{
    vector<double> res = Interpolate(0, 0, 4, 1);
    EXPECT_EQ(res.size(), 5);
    EXPECT_EQ(res[1], 0.25);
    EXPECT_EQ(res[2], 0.5);
    EXPECT_EQ(res[3], 0.75);
}

TEST(Utils, Interpolate5)
{
    vector<double> res = Interpolate(0, 0, 5, -0.5);
    EXPECT_EQ(res.size(), 6);
    EXPECT_EQ(res[1], -0.1);
    EXPECT_EQ(res[2], -0.2);
    // EXPECT_EQ(res[3], -0.3);
}
