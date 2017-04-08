#pragma once

#include "mesh.h"
#include "model.h"

#include <memory>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelData
{
    friend class ModelLoader;
private:
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> tex_coords;
    std::vector<uint>      indices;

public:
    ModelData() = default;

public:
    ColoredModel* toColoredModel() const
    {
        return new ColoredModel(IndexedMesh(positions, normals, indices));
    }
};

class ModelLoader
{
public:
    static std::unique_ptr<ModelData> LoadModel(const std::string& model_path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile( model_path.data(),
                aiProcess_Triangulate            |
                aiProcess_GenSmoothNormals       |
                aiProcess_FlipUVs                |
                aiProcess_JoinIdenticalVertices );

          // If the import failed, report it
          if(!scene)
          {
            qDebug() << importer.GetErrorString();
            return nullptr;
          }

        std::unique_ptr<ModelData> model_data{new ModelData()};

        const aiMesh* model = scene->mMeshes[0];
        for(unsigned int i = 0; i < model->mNumVertices; i++)
        {
            const aiVector3D pos = model->mVertices[i];
            const aiVector3D normal = model->mNormals[i];
            const aiVector3D tex_coord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiVector3D{0.0f, 0.0f, 0.0f};

            model_data->positions.push_back(QVector3D(pos.x, pos.y, pos.z));
            model_data->tex_coords.push_back(QVector2D(tex_coord.x, tex_coord.y));
            model_data->normals.push_back(QVector3D(normal.x, normal.y, normal.z));
        }

        for(unsigned int i = 0; i < model->mNumFaces; i++)
        {
            const aiFace& face = model->mFaces[i];
            assert(face.mNumIndices == 3);
            model_data->indices.push_back(face.mIndices[0]);
            model_data->indices.push_back(face.mIndices[1]);
            model_data->indices.push_back(face.mIndices[2]);
        }

        return std::move(model_data);
    }
};
