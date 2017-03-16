#pragma once

#include "camera.h"
#include "shader_program.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Scene : public QOpenGLWidget, public QOpenGLFunctions
{
    Camera camera;
    ShaderProgram program;
public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height);
    void paintGL() override;

private:
    void just_a_test();
};

