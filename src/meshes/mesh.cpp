#include "mesh.hpp"

Sphere Mesh::GetBoundingSphere() const
{
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;
    double minX = 0;
    double minY = 0;
    double minZ = 0;
    vector<shared_ptr<Vec3>> vertices = this->GetUniqueVertices();
    // first calculate the center
    for (const auto vertice : vertices)
    {
        if (vertice->x > maxX)
        {
            maxX = vertice->x;
        }
        if (vertice->x < minX)
        {
            minX = vertice->x;
        }
        if (vertice->y > maxY)
        {
            maxY = vertice->y;
        }
        if (vertice->y < minY)
        {
            minY = vertice->y;
        }
        if (vertice->z > maxZ)
        {
            maxZ = vertice->z;
        }
        if (vertice->z < minZ)
        {
            minZ = vertice->z;
        }
    }
    Vec3 center = Vec3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
    double radius = 0;
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