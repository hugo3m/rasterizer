#pragma once

#include <array>
#include <memory>
#include "model.hpp"
#include "../math/vec.hpp"
#include "../math/triangle.hpp"

using namespace std;

class TriangleModel : public Model
{
private:
    shared_ptr<Triangle> _triangle;

public:
    TriangleModel(shared_ptr<Triangle> t);

    vector<shared_ptr<Triangle>> GetTriangles() const;
};