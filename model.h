#pragma once

#include "mesh.h"
#include "shader_program.h"

#include <memory>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class Model
{
private:
    std::shared_ptr<Mesh> mesh;
    std::vector<QVector4D> colors;

    QOpenGLVertexArrayObject vertexArrayObject;
    std::vector<QOpenGLBuffer> vertexBufferObjects;

public:
    Model(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors)
        : mesh{new Mesh(positions)}, colors{ colors }
    {
        InitializeModel();
    }
    Model(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors, const std::vector<uint>& indices)
        : mesh{new IndexedMesh(positions, indices)}, colors{ colors }
    {
        InitializeModel();
    }

public:
    void BindShaderProgram(QOpenGLShaderProgram& program);

    virtual void InitializeModel();
    virtual void Draw(QOpenGLFunctions_4_3_Core* context);
    virtual void Draw(QOpenGLFunctions* context);

private:
    void GenerateObjects();
    void InitializeBuffers();

};

