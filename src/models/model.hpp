#pragma once

#include <vector>
#include "../math/triangle.hpp"

class Model
{
public:
    virtual vector<shared_ptr<Triangle>> GetTriangles() const = 0;
};