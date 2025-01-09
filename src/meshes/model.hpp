#pragma once

#include <vector>
#include "../math/sphere.hpp"
#include "../math/triangle.hpp"

class Model
{
public:
    virtual vector<shared_ptr<Triangle>> GetTriangles() const = 0;

    virtual vector<shared_ptr<Vec3>> GetUniqueVertices() const = 0;

    virtual Sphere GetBoundingSphere() const;
};