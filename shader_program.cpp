
#include "shader_program.h"


void ShaderProgram::InitShader()
{
//    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, program_name +".vs"));
//    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, program_name +".fs"));

    if(!program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 vertex;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = matrix * vertex;\n"
        "}"));
    if(!program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "uniform mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "   gl_FragColor = color;\n"
        "}"));

    if(!program.link());
    if(!program.bind());
}

void ShaderProgram::Update(const Transform& transformation, const Camera& camera, const QColor& color)
{
    int matrixLocation = program.uniformLocation("matrix");
    int colorLocation = program.uniformLocation("color");
    program.setUniformValue(matrixLocation, camera.ViewProjection() * transformation.Model());
    program.setUniformValue(colorLocation, color);
}

void ShaderProgram::Update(const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& projection, const QColor& color)
{
    int matrixLocation = program.uniformLocation("matrix");
    int colorLocation = program.uniformLocation("color");
    program.setUniformValue(matrixLocation, projection * view * model);
    program.setUniformValue(colorLocation, color);
}

void ShaderProgram::BindData(const GLfloat* data)
{
    int vertexLocation = program.attributeLocation("vertex");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeArray(vertexLocation, data, 3);
}
