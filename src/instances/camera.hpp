#pragma once

#include <array>

#include "../render/viewport.hpp"
#include "../math/plane.hpp"
#include "../math/matrix.hpp"
#include "transform.hpp"

using namespace std;

class Camera
{
private:
    Viewport _viewport;
    Transform _transform;
    array<Plane, 5> _clippingPlanes;

public:
    Camera(Viewport viewport, Transform transform);

    array<Plane, 5> GenerateClippingPlanes() const;

    void SetClippingPlanes(array<Plane, 5> clippingPlanes);

    array<Plane, 5> GetClippingPlanes() const;

    Viewport GetViewport() const;

    Matrix GenerateMatrixCamera() const;

    Transform GetTransform() const;

    void SetTransform(Transform value);
};