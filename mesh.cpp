
#include "mesh.h"
#include <QHash>

uint qHash(const QVector3D &v)
{
    return qHash( QString( "%1x%2x%3" ).arg(v.x()).arg(v.y()).arg(v.z()) ) ;
}

void Mesh::CalculateNormals()
{
    if(positions.size() < 2) return;

    QHash<QVector3D, std::vector<uint>> positions_map;
    for(uint i = 0; i < positions.size(); ++i) {
        positions_map[positions[i]].push_back(i);
    }

    for(uint i = 0; i < positions.size(); i += 3)
    {
        auto pos1 = positions[i];
        auto pos2 = positions[i + 1];
        auto pos3 = positions[i + 2];

        auto vec1 = pos2 - pos1;
        auto vec2 = pos3 - pos1;

        auto normal = QVector3D::normal(vec1, vec2);

        for(uint j = 0; j < 3; ++j)
        {
            for(auto index : positions_map[positions[j]]) {
                normals[index] += normal;
            }
        }
    }
    for(auto& normal : normals){
        normal.normalize();
    }
}

void IndexedMesh::CalculateNormals()
{
    if(positions.size() < 2) return;
    for(uint i = 0; i < indices.size(); i += 3)
    {
        auto index0 = indices[i];
        auto index1 = indices[i + 1];
        auto index2 = indices[i + 2];

        auto vec1 = positions[index1] - positions[index0];
        auto vec2 = positions[index2] - positions[index0];

        auto normal = QVector3D::normal(vec1, vec2);

        normals[index0] += normal;
        normals[index1] += normal;
        normals[index2] += normal;
    }

    for(auto& normal : normals){
        normal.normalize();
    }
}
