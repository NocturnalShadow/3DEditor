#include "scene_item.h"

SceneItem::SceneItem(const IModel &_model, ShaderProgram *_program)
    : model{ _model.Clone() },
      program{ _program }
{
    model->InitializeModel();
}

SceneItem::SceneItem(IModel&& _model)
    : model{ _model.Move() }
{
    if(!model->isInitialized()) {
        model->InitializeModel();
    }
}

SceneItem::SceneItem(SceneItem&& item)
    : model{ item.model->Move() },
      transformation{ std::move(item.transformation) },
      program{ std::move(item.program) }
{

}

SceneItem::SceneItem(const SceneItem &item)
    : model{ item.model->Clone() },
      transformation{ item.transformation },
      program{ item.program }
{
    model->InitializeModel();
}

SceneItem& SceneItem::operator=(const SceneItem &item)
{
    model.reset(item.model->Clone());
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
