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
    std::unique_ptr<Mesh> mesh;
    std::vector<QVector4D> colors;

    QOpenGLVertexArrayObject vertexArrayObject;
    std::vector<QOpenGLBuffer> vertexBufferObjects;

protected:
    bool is_initialized = false;

public:
    Model(Model&& model);
    Model(const Model& model);
    Model(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors);
    Model(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors, const std::vector<uint>& indices);

public:
    void BindShaderProgram(QOpenGLShaderProgram& program);

    virtual void InitializeModel();
    virtual void Draw(QOpenGLFunctions_4_3_Core* context);
    virtual void Draw(QOpenGLFunctions* context);

    bool isInitialized() const { return is_initialized; }

protected:
    void InitializeBaseModel();

private:
    void GenerateObjects();
    void InitializeBuffers();
};

