#pragma once

#include "camera.h"
#include "transform.h"

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class ShaderProgram
{
private:
    QOpenGLShaderProgram program;

    QString program_name;

public:
    ShaderProgram(QString program_name)
        : program_name{program_name}
    {
    }

public:
    void InitShader();

    void Bind()     { program.bind(); }
    void Unbind()   { program.release(); }

    void Update(const ICamera &camera);
    void Update(const Transformation &transformation);
    void Update(const Transformation &transformation, const ICamera &camera);
    void Update(const QMatrix4x4 &model, const QMatrix4x4 &view, const QMatrix4x4 &projection);

    QOpenGLShaderProgram& Get() { return program; }
};

