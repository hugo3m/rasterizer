#include <gtest/gtest.h>
#include "../src/render/rgba.hpp"

// Demonstrate some basic assertions.
TEST(RgbaTest, Unpack)
{
    RGBA rgba = RGBA(0, 130, 320, -10);
    array<int, 4> array = rgba.Unpack();
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 130);
    EXPECT_EQ(array[2], 255);
    EXPECT_EQ(array[3], 0);
}

// Demonstrate some basic assertions.
TEST(RgbaTest, Multiply1)
{
    RGBA rgba = RGBA(0, 0, 255, 255);
    RGBA res = rgba * 0;
    array<int, 4> array = res.Unpack();
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 255);
}

// Demonstrate some basic assertions.
TEST(RgbaTest, Multiply2)
{
    RGBA rgba = RGBA(100, 1, 0, 10);
    RGBA res = rgba * 10;
    array<int, 4> array = res.Unpack();
    EXPECT_EQ(array[0], 255);
    EXPECT_EQ(array[1], 10);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 10);
}