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


class IModel
{
protected:
    std::unique_ptr<Mesh> mesh;

    std::unique_ptr<QOpenGLVertexArrayObject> vertexArrayObject;
    std::vector<QOpenGLBuffer> vertexBufferObjects;

protected:
    bool is_initialized = false;

protected:
    IModel(IModel&& model) = default;
    IModel(const IModel& model);

public:
    IModel(const Mesh& mesh);
    IModel(const std::vector<QVector3D>& positions);
    IModel(const std::vector<QVector3D>& positions, const std::vector<uint>& indices);

public:
    virtual void BindShaderProgram(QOpenGLShaderProgram& program);

    virtual void InitializeModel();
    virtual void Draw(QOpenGLFunctions* context);
    virtual void Draw(QOpenGLFunctions_4_3_Core* context);

    virtual IModel* Clone() const = 0;
    virtual IModel* Move()        = 0;

    bool isInitialized()   const { return is_initialized;  }

protected:
    void InitializeBaseModel();
    void BindBaseShaderProgram(QOpenGLShaderProgram& program);

    void DrawBase(QOpenGLFunctions* glFunctions);
    void DrawBase(QOpenGLFunctions_4_3_Core* glFunctions);

private:
    void GenerateObjects();
    void InitializeBuffers();
};


class ColoredModel : public IModel
{
protected:
    std::vector<QVector4D> colors;

protected:
    ColoredModel(ColoredModel&& model)      = default;
    ColoredModel(const ColoredModel& model) = default;

public:
    ColoredModel(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors)
        : IModel{ positions }, colors{ colors }
    {
    }
    ColoredModel(const std::vector<QVector3D>& positions, std::vector<QVector4D> colors, const std::vector<uint>& indices)
        : IModel{ positions, indices }, colors{ colors }
    {
    }

public:
    virtual ColoredModel* Clone()  const override { return new ColoredModel(*this);             }
    virtual ColoredModel* Move()         override { return new ColoredModel(std::move(*this));  }

public:
    virtual void InitializeModel() override
    {
        InitializeBaseModel();

        vertexArrayObject->bind();
        vertexBufferObjects.emplace_back(QOpenGLBuffer::VertexBuffer);
        vertexBufferObjects.back().create();
        vertexBufferObjects[3].bind();
        vertexBufferObjects[3].allocate(colors.data(), (int)colors.size() * sizeof(colors[0]));
        vertexBufferObjects[3].setUsagePattern(QOpenGLBuffer::StreamDraw);
        vertexArrayObject->release();

        is_initialized = true;
    }
    virtual void Draw(QOpenGLFunctions* context) override
    {
        DrawBase(context);
    }
    virtual void Draw(QOpenGLFunctions_4_3_Core* context) override
    {
        DrawBase(context);
    }
    virtual void BindShaderProgram(QOpenGLShaderProgram& program) override
    {
        BindBaseShaderProgram(program);

        vertexArrayObject->bind();
        vertexBufferObjects[3].bind();

        program.enableAttributeArray("color");
        program.setAttributeArray("color", GL_FLOAT, 0, 4);

        vertexArrayObject->release();
    }

};

