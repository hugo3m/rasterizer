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

vector<shared_ptr<Triangle>> Instance::GetSceneTriangles(const Matrix &matrixCamera) const
{
    vector<shared_ptr<Triangle>> res;
    Matrix matrixFactor = this->GenerateMatrixInstance() * matrixCamera;
    vector<shared_ptr<Triangle>> triangles = this->GetMesh()->GetTriangles();
    for (auto triangle : triangles)
    {
        array<shared_ptr<Vec3>, 3> vertices = triangle->GetVertices();
        // printf("Triangle before multiplication(%f, %f, %f) v1(%f, %f, %f) v2(%f, %f, %f) \n", vertices[0]->x, vertices[0]->y, vertices[0]->z, vertices[1]->x, vertices[1]->y, vertices[1]->z, vertices[2]->x, vertices[2]->y, vertices[2]->z);
        Triangle matrixTriangle = (*triangle) * matrixFactor;
        vertices = matrixTriangle.GetVertices();
        res.push_back(make_shared<Triangle>(vertices[0], vertices[1], vertices[2]));
    }
    return res;
}

vector<shared_ptr<Triangle>> Instance::GetRawTriangles() const
{
    return this->_mesh->GetTriangles();
};