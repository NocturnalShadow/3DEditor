#pragma once

#include "camera.h"
#include "shader_program.h"
#include "model.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>

class Scene : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core
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

