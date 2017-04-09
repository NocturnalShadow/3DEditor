#pragma once

#include "shader_program.h"

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class IDrawable
{
protected:
    GLenum primitive                = GL_TRIANGLES;

public:
    void SetPrimitive(GLenum _primitive) {
        primitive = _primitive;
    }
public:
    virtual void Draw(QOpenGLFunctions* view)               = 0;
    virtual void Draw(QOpenGLFunctions_4_3_Core* view)      = 0;
    virtual void BindShaderProgram(ShaderProgram* _program) = 0;
};
