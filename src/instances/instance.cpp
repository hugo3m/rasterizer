#include "instance.hpp"

Instance::Instance(shared_ptr<Mesh> mesh, Transform transform, shared_ptr<Material> material) : _mesh(mesh), _transform(transform), _material(material) {};

shared_ptr<Mesh> Instance::GetMesh() const
{
    return this->_mesh;
};

Transform Instance::GetTransform() const
{
    return this->_transform;
};

shared_ptr<Material> Instance::GetMaterial() const
{
    return this->_material;
};

Matrix Instance::GenerateMatrixInstance() const
{
    Vec3 translation = this->_transform.GetTranslation();
    Vec3 scale = this->_transform.GetScale();
    Matrix matrixTranslation = Matrix({1, 0, 0, translation.x, 0, 1, 0, translation.y, 0, 0, 1, translation.z, 0, 0, 0, 1}, 4, 4);
    Matrix matrixScale = Matrix({scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1}, 4, 4);
    return matrixTranslation * matrixScale * this->_transform.GetRotation().GenerateMatrixRotation();
}

Sphere Instance::GetBoundingSphere() const
{
    Sphere meshBoundingSphere = this->GetMesh()->GetBoundingSphere();
    Transform transform = this->GetTransform();
    Vec3 translate = transform.GetTranslation();
    Vec3 scale = transform.GetScale();
    double maxScale = max(scale.x, max(scale.y, scale.z));
    return Sphere(meshBoundingSphere.GetCenter() + translate, maxScale * meshBoundingSphere.GetRadius());
}