
#include "shader_program.h"


void ShaderProgram::InitShader()
{
    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, program_name +".vs"))
        qDebug() << "Cannot compile vertex shader " + program_name +".vs" << endl;
    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, program_name +".fs"))
        qDebug() << "Cannot compile fragment shader " + program_name +".fs" << endl;
    if(!program.link())
        qDebug() << "Cannot link shader program " + program_name << endl;
}

void ShaderProgram::Update(const Transform& transformation, const Camera& camera)
{
    program.setUniformValue("matrix", camera.ViewProjection() * transformation.Model());
}

void ShaderProgram::Update(const QMatrix4x4 &matrix)
{
     program.setUniformValue("matrix", matrix);
}

void ShaderProgram::Update(const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& projection)
{
    program.setUniformValue(program.uniformLocation("matrix"), projection * view * model);
}
