#include <gtest/gtest.h>
#include "../src/meshes/cube.hpp"

TEST(CubeTest, GetBoundingCirlce)
{
    // The four "front" vertices
    shared_ptr<Vec3> v1 = make_shared<Vec3>(0, 0, 0);
    shared_ptr<Vec3> v2 = make_shared<Vec3>(1, 0, 0);
    shared_ptr<Vec3> v3 = make_shared<Vec3>(0, 1, 0);
    shared_ptr<Vec3> v4 = make_shared<Vec3>(1, 1, 0);
    // The four "back" vertices
    shared_ptr<Vec3> v5 = make_shared<Vec3>(0, 0, 1);
    shared_ptr<Vec3> v6 = make_shared<Vec3>(1, 0, 1);
    shared_ptr<Vec3> v7 = make_shared<Vec3>(0, 1, 1);
    shared_ptr<Vec3> v8 = make_shared<Vec3>(1, 1, 1);
    // the triangle model
    shared_ptr<Triangle> t1 = make_shared<Triangle>(v1, v2, v3);
    shared_ptr<Triangle> t2 = make_shared<Triangle>(v1, v3, v4);
    shared_ptr<Triangle> t3 = make_shared<Triangle>(v5, v1, v2);
    shared_ptr<Triangle> t4 = make_shared<Triangle>(v5, v4, v8);
    shared_ptr<Triangle> t5 = make_shared<Triangle>(v6, v5, v8);
    shared_ptr<Triangle> t6 = make_shared<Triangle>(v6, v8, v7);
    shared_ptr<Triangle> t7 = make_shared<Triangle>(v2, v6, v7);
    shared_ptr<Triangle> t8 = make_shared<Triangle>(v2, v7, v3);
    shared_ptr<Triangle> t9 = make_shared<Triangle>(v5, v6, v2);
    shared_ptr<Triangle> t10 = make_shared<Triangle>(v5, v2, v1);
    shared_ptr<Triangle> t11 = make_shared<Triangle>(v3, v7, v8);
    shared_ptr<Triangle> t12 = make_shared<Triangle>(v3, v8, v4);
    // the cube model
    CubeModel c1 = CubeModel(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);

    Sphere boundingSphere = c1.GetBoundingSphere();
    EXPECT_TRUE(boundingSphere.GetCenter() == Vec3(0.5, 0.5, 0.5));
    EXPECT_EQ(boundingSphere.GetRadius(), Vec3(0.5, 0.5, 0.5).Norm());
}