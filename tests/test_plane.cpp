#include <gtest/gtest.h>
#include "../src/math/plane.hpp"

TEST(PlaneTest, New)
{
    Plane plane1 = Plane(Vec3(1, 0, 0), 1);
    Plane plane2 = Plane(Vec3(3, 0, 0), 3);
    EXPECT_TRUE(plane1.GetNormal() == plane2.GetNormal());
}

TEST(PlaneTest, IsInFront1)
{
    Plane plane = Plane(Vec3(1, 0, 0), 0);
    EXPECT_TRUE(plane.IsInFront(Vec3(2, 0, 0)));
    EXPECT_TRUE(plane.IsInFront(Vec3(2, 2, 2)));
    EXPECT_FALSE(plane.IsInFront(Vec3(0, 0, 0)));
    EXPECT_EQ(plane.IsInFront(Vec3(-1, 0, 0)), false);
}

TEST(PlaneTest, IsInFront2)
{
    Plane plane = Plane(Vec3(1, 0, 0), 1);
    EXPECT_EQ(plane.IsInFront(Vec3(2, 0, 0)), true);
    EXPECT_EQ(plane.IsInFront(Vec3(2, 2, 2)), true);
    EXPECT_EQ(plane.IsInFront(Vec3(0, 0, 0)), false);
    EXPECT_EQ(plane.IsInFront(Vec3(1, 0, 0)), false);
}

TEST(PlaneTest, SignedDist)
{
    Plane plane = Plane(Vec3(1, 0, 0), 0);
    EXPECT_EQ(plane.SignedDist(Vec3(0, 0, 0)), 0);
    EXPECT_EQ(plane.SignedDist(Vec3(2, 0, 0)), 2);
    EXPECT_EQ(plane.SignedDist(Vec3(2, 2, 0)), 2);
    EXPECT_EQ(plane.SignedDist(Vec3(-2, 0, 0)), -2);
}

TEST(PlaneTest, HasIntersection)
{
    Plane plane = Plane(Vec3(1, 0, 0), 0);
    EXPECT_FALSE(plane.HasIntersection(Vec3(0, 0, 0), Vec3(0, 1, 0)));
    EXPECT_TRUE(plane.HasIntersection(Vec3(0, 0, 0), Vec3(1, 0, 0)));
    EXPECT_TRUE(plane.HasIntersection(Vec3(0, 0, 0), Vec3(-1, 0, 0)));
    EXPECT_FALSE(plane.HasIntersection(Vec3(1, 0, 0), Vec3(1, 1, 0)));
}

TEST(PlaneTest, Intersection)
{
    Plane plane = Plane(Vec3(1, 0, 0), 0);
    EXPECT_TRUE(plane.Intersection(Vec3(0, 0, 0), Vec3(1, 1, 0)) == Vec3(0, 0, 0));
    EXPECT_TRUE(plane.Intersection(Vec3(-1, 0, 0), Vec3(1, 0, 0)) == Vec3(0, 0, 0));
    EXPECT_TRUE(plane.Intersection(Vec3(-1, 1, 0), Vec3(1, 1, 0)) == Vec3(0, 1, 0));
}