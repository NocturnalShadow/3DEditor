#pragma once

#include "model.h"
#include "drawable.h"
#include "transform.h"
#include "shader_program.h"

#include <memory>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class SceneItem : public IDrawable
{
private:
    std::unique_ptr<IModel> model;
    Transformation transformation;
    ShaderProgram* program;

public:
    SceneItem() = default;
    SceneItem(IModel&& _model);
    SceneItem(SceneItem&& item);
    SceneItem(const SceneItem& item);
    SceneItem(const IModel& _model, ShaderProgram* _program = nullptr);

    SceneItem& operator=(const SceneItem& item);

public:
    Transformation& Transform() { return transformation; }

    void BindShaderProgram(ShaderProgram* _program) override;

    void Draw(QOpenGLFunctions* view) override;
    void Draw(QOpenGLFunctions_4_3_Core* view) override;
};

