#include "scene_item.h"

SceneItem::SceneItem(const Model &_model, ShaderProgram *_program)
    : model{ std::make_shared<Model>(_model) },
      program{ _program }
{
    model->InitializeModel();
}

SceneItem::SceneItem(Model &&_model)
    : model{ std::make_shared<Model>(std::move(_model)) }
{
    if(!model->isInitialized()) {
        model->InitializeModel();
    }
}

SceneItem::SceneItem(const SceneItem &item)
    : model{ std::make_shared<Model>(*item.model) },
      transformation{ item.transformation },
      program{ item.program }
{
    model->InitializeModel();
}

SceneItem &SceneItem::operator=(const SceneItem &item)
{
    model = std::make_shared<Model>(*item.model);
    transformation = item.transformation;
    program = item.program;
    model->InitializeModel();
    return *this;
}

void SceneItem::BindShaderProgram(ShaderProgram *_program)
{
    program = _program;
    model->BindShaderProgram(program->Get());
}

void SceneItem::Draw(QOpenGLFunctions *view)
{
    program->Update(transformation);
    model->Draw(view);
}

void SceneItem::Draw(QOpenGLFunctions_4_3_Core *view)
{
    program->Update(transformation);
    model->Draw(view);
}
