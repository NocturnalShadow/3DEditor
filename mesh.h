#pragma once

#include <vector>
#include <QVector3D>
#include <QDebug>

class Mesh
{
public:
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;

public:
    Mesh(const std::vector<QVector3D>& _positions)
        : positions{_positions}, normals(_positions.size())
    {
    }

public:
    void InitializeMesh() {
        CalculateNormals();
    }

    const QVector3D* Positions()   const { return positions.data();   }
    const QVector3D* Normals()     const { return normals.data();     }

    size_t SizeOfPositions()       const { return positions.size() * sizeof(positions[0]);  }
    size_t SizeOfNormals()         const { return normals.size() * sizeof(normals[0]);      }

    virtual uint VertexCount()     const { return (uint) positions.size();   }

private:
    virtual void CalculateNormals();
};


class IndexedMesh : public Mesh
{
private:
    std::vector<uint> indices;

public:
    IndexedMesh(const std::vector<QVector3D>& _positions, const std::vector<uint>& _indices)
        : Mesh{_positions}, indices{_indices}
    {
    }

public:
     const uint* Indices()         const { return indices.data();                       }
     size_t SizeOfIndices()        const { return indices.size() * sizeof(indices[0]);  }
     virtual uint VertexCount()    const { return (uint) indices.size();                }

private:
    void CalculateNormals() override;
};

