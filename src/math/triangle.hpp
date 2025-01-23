#pragma once

#include <array>
#include <memory>
#include "../math/vec.hpp"
#include "../math/matrix.hpp"

using namespace std;

class Triangle
{
private:
    array<shared_ptr<Vec3>, 3> _vertices;

public:
    Triangle(const shared_ptr<Vec3> v1, const shared_ptr<Vec3> v2, const shared_ptr<Vec3> v3);

    Triangle(const Triangle &triangle);

    array<shared_ptr<Vec3>, 3> GetVertices() const;

    bool IsFacing(const Vec3 &origin) const;

    bool HasIntersection(const Vec3 &origin, const Vec3 &direction) const;

    Triangle Matrixed(const Matrix &matrixCamera, const Matrix &matrixInstance) const;

    Vec3 GetNormal() const;
};