#pragma once

#include "transform.h"
#include "camera.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QColor>

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
    void Update(const Transform &transformation, const Camera &camera);
    void Update(const QMatrix4x4 & matrix);
    void Update(const QMatrix4x4 &model, const QMatrix4x4 &view, const QMatrix4x4 &projection);

    QOpenGLShaderProgram& Get() { return program; }
};

