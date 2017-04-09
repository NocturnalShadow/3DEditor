#pragma once

#include <vector>

#include <QDebug>
#include <QVector3D>

class Mesh
{
protected:
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;

private:
    bool is_normalized   = false;

protected:
    Mesh(Mesh&& mesh)      = default;
    Mesh(const Mesh& mesh) = default;

public:
    Mesh(std::vector<QVector3D>&& _positions)
        : positions{std::move(_positions)}, normals{_positions.size() }
    {
    }
    Mesh(const std::vector<QVector3D>& _positions)
        : positions{_positions}, normals{_positions.size() }
    {
    }

    Mesh(std::vector<QVector3D>&& _positions, std::vector<QVector3D>&& normals)
        : positions{std::move(_positions)}, normals{ std::move(normals) }, is_normalized{ true }
    {
    }
    Mesh(const std::vector<QVector3D>& _positions, const std::vector<QVector3D>& normals)
        : positions{_positions}, normals{ normals }, is_normalized{ true }
    {
    }

public:
    void InitializeMesh()
    {
        if(!is_normalized)
        {
            CalculateNormals();
            is_normalized = true;
        }
    }
    void ResetNormals()
    {
        normals.clear();
        normals.resize(positions.size());
        is_normalized = false;
    }

    size_t SizeOfPositions()       const { return positions.size() * sizeof(positions[0]);  }
    size_t SizeOfNormals()         const { return normals.size() * sizeof(normals[0]);      }

    const QVector3D* Positions()   const { return positions.data();        }
    const QVector3D* Normals()     const { return normals.data();          }

    virtual uint VertexCount()     const { return (uint) positions.size(); }
    virtual Mesh* Clone()          const
    {
        Mesh* mesh                   = new Mesh(positions);
        mesh->normals                = normals;
        mesh->is_normalized          = is_normalized;
        return mesh;
    }
    virtual Mesh* Move()
    {
        Mesh* mesh                   = new Mesh(std::move(positions));
        mesh->normals                = std::move(normals);
        mesh->is_normalized          = is_normalized;
        is_normalized                = false;
        return mesh;
    }

private:
    virtual void CalculateNormals();
};


class IndexedMesh final : public Mesh
{
private:
    std::vector<uint> indices;

public:
    IndexedMesh(IndexedMesh&& mesh)      = default;
    IndexedMesh(const IndexedMesh& mesh) = default;

    IndexedMesh(std::vector<QVector3D>&& _positions, std::vector<uint>&& _indices)
        : Mesh{std::move(_positions)}, indices{std::move(_indices)}
    {
    }
    IndexedMesh(const std::vector<QVector3D>& _positions, const std::vector<uint>& _indices)
        : Mesh{_positions}, indices{_indices}
    {
    }
    IndexedMesh(std::vector<QVector3D>&& _positions, std::vector<QVector3D>&& _normals, std::vector<uint>&& _indices)
        : Mesh{std::move(_positions), std::move(_normals)}, indices{std::move(_indices)}
    {
    }
    IndexedMesh(const std::vector<QVector3D>& _positions, const std::vector<QVector3D>& _normals, const std::vector<uint>& _indices)
        : Mesh{_positions, _normals}, indices{_indices}
    {
    }

public:
     const uint* Indices()         const { return indices.data();                       }
     size_t SizeOfIndices()        const { return indices.size() * sizeof(indices[0]);  }
     virtual uint VertexCount()    const { return (uint) indices.size();                }

     IndexedMesh* Clone() const override;
     IndexedMesh* Move()        override;

private:
    void CalculateNormals() override;

};

