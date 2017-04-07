
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

void ShaderProgram::Update(const ICamera& camera)
{
    program.setUniformValue("View", camera.View());
    program.setUniformValue("Projection", camera.Projection());
}

void ShaderProgram::Update(const QMatrix4x4& model)
{
    program.setUniformValue("Model", model);
}

void ShaderProgram::Update(const Transformation& transformation)
{
    program.setUniformValue("Model", transformation.Model());
}

void ShaderProgram::Update(const Transformation& transformation, const ICamera& camera)
{
    Update(camera);
    Update(transformation);
}

void ShaderProgram::Update(const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& projection)
{
    program.setUniformValue("Model", model);
    program.setUniformValue(program.uniformLocation("View"), view);
    program.setUniformValue(program.uniformLocation("Projection"), projection);
}
