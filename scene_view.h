#pragma once

#include "gl_debug.h"

#include "model.h"
#include "camera.h"
#include "scene_item.h"
#include "shader_program.h"

#include <memory>

#include <QOpenGLFunctions_4_3_Core>

class SceneItem;
class SceneView
{
private:
    ShaderProgram program;
    std::unique_ptr<SceneViewCamera> camera;
    QOpenGLFunctions_4_3_Core* glFunctions;

    std::vector<SceneItem*> items;

public:
    SceneView(QOpenGLFunctions_4_3_Core* _glFunctions, QString program_name)
        : glFunctions{ _glFunctions }, program{ program_name }, camera{new SceneViewCamera()}
    {
    }

public:
    void Initialize();
    void Paint();
    void AddItem(SceneItem* item);
    void Resize(int width, int height);
    SceneViewCamera* Camera() {
        return camera.get();
    }
    void BindShader() {
        program.Bind();
    }
};

