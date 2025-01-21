#include "camera.hpp"

Camera::Camera(Viewport viewport, Transform transform) : _viewport(viewport), _transform(transform), _clippingPlanes(GenerateClippingPlanes()) {};

array<Plane, 5> Camera::GenerateClippingPlanes() const
{
    return {
        Plane(Vec3(0, 0, 1), this->_viewport.depth),
        Plane(Vec3(1 / sqrt(2), 0, 1 / sqrt(2)), 0),
        Plane(Vec3(-1 / sqrt(2), 0, 1 / sqrt(2)), 0),
        Plane(Vec3(0, 1 / sqrt(2), 1 / sqrt(2)), 0),
        Plane(Vec3(0, -1 / sqrt(2), 1 / sqrt(2)), 0),
    };
};

void Camera::SetClippingPlanes(array<Plane, 5> clippingPlanes)
{
    this->_clippingPlanes = clippingPlanes;
};

array<Plane, 5> Camera::GetClippingPlanes() const
{
    return this->_clippingPlanes;
};

Viewport Camera::GetViewport() const
{
    return this->_viewport;
}

Matrix Camera::GenerateMatrixCamera() const
{
    Vec3 translation = this->_transform.GetTranslation();
    Matrix translationMatrix = Matrix({1, 0, 0, translation.x, 0, 1, 0, translation.y, 0, 0, 1, translation.z, 0, 0, 0, 1}, 4, 4);
    return translationMatrix.Inverse();
}

Transform Camera::GetTransform() const
{
    return this->_transform;
}