#include "mesh.hpp"

Sphere Mesh::GetBoundingSphere() const
{
    Vec3 center = Vec3(0, 0, 0);
    double radius = 0;
    vector<shared_ptr<Vec3>> vertices = this->GetUniqueVertices();
    // first calculate the center
    for (const auto vertice : vertices)
    {
        center = center + (*vertice);
    }
    center = center / vertices.size();
    // then from center
    // find radius from maximal distance
    for (const auto vertice : vertices)
    {
        double norm = ((*vertice) - center).Norm();
        if (norm > radius)
        {
            radius = norm;
        }
    }
    return Sphere(center, radius);
}