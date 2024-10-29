#include <gtest/gtest.h>
#include "../src/render/rgba.hpp"

// Demonstrate some basic assertions.
TEST(RgbaTest, Render)
{
    RGBA rgba = RGBA(0, 130, 320, -10);
    array<int, 4> array = rgba.Unpack();
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 130);
    EXPECT_EQ(array[2], 255);
    EXPECT_EQ(array[3], 0);
}