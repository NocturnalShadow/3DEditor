#pragma once

#include "model.h"
#include "transform.h"
#include "shader_program.h"

#include <memory>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class SceneItem
{
private:
    std::shared_ptr<Model> model;
    Transformation transformation;
    ShaderProgram* program;

public:
    SceneItem() = default;
    SceneItem(Model&& _model);
    SceneItem(const SceneItem& item);
    SceneItem(const Model& _model, ShaderProgram* _program = nullptr);

    SceneItem& operator=(const SceneItem& item);

public:
    Transformation& Transform() { return transformation; }

    void BindShaderProgram(ShaderProgram* _program);

    void Draw(QOpenGLFunctions* view);
    void Draw(QOpenGLFunctions_4_3_Core* view);
};

