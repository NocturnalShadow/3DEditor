#pragma once

#include "model.h"
#include "transform.h"
#include "shader_program.h"

#include <memory>

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class Scene;
class SceneItem
{
private:
    std::shared_ptr<Model> model;
    Transformation transformation;
    ShaderProgram* program;

public:
    SceneItem() = default;
    SceneItem(const Model& _model, ShaderProgram* _program = nullptr)
        : model{ std::make_shared<Model>(_model) },
          program{ _program }
    {
        model->InitializeModel();
    }
    SceneItem(Model&& _model)
        : model{ std::make_shared<Model>(std::move(_model)) }
    {
        if(!model->isInitialized()) {
            model->InitializeModel();
        }
    }
    SceneItem(const SceneItem& item)
        : model{ std::make_shared<Model>(*item.model) },
          transformation{ item.transformation },
          program{ item.program }
    {
        model->InitializeModel();
    }

    SceneItem& operator=(const SceneItem& item)
    {
        model = std::make_shared<Model>(*item.model);
        transformation = item.transformation;
        program = item.program;
        model->InitializeModel();
        return *this;
    }

public:
    Transformation& Transform() {
        return transformation;
    }

    void BindShaderProgram(ShaderProgram* _program)
    {
        program = _program;
        model->BindShaderProgram(program->Get());
    }

    void Draw(QOpenGLFunctions* scene)
    {
        program->Update(transformation);
        model->Draw(scene);
    }
    void Draw(QOpenGLFunctions_4_3_Core* scene)
    {
        program->Update(transformation);
        model->Draw(scene);
    }
};

