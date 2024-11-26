#pragma once

#include <array>
#include <memory>
#include "../math/vec.hpp"

using namespace std;

class Triangle
{
private:
    array<shared_ptr<Vec3>, 3> _vertices;

public:
    Triangle(shared_ptr<Vec3> v1, shared_ptr<Vec3> v2, shared_ptr<Vec3> v3);
    array<shared_ptr<Vec3>, 3> GetVertices() const;
};