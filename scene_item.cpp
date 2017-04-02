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

void SceneItem::Draw(QOpenGLFunctions* glFunctions)
{
    glFunctions->glEnable(GL_STENCIL_TEST);
    glFunctions->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glFunctions->glStencilFunc(GL_ALWAYS, id, -1);

    program->Update(transformation);
    model->Draw(glFunctions);
}

void SceneItem::Draw(QOpenGLFunctions_4_3_Core* glFunctions)
{
    glFunctions->glEnable(GL_STENCIL_TEST);
    glFunctions->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glFunctions->glStencilFunc(GL_ALWAYS, id, -1);

    program->Update(transformation);
    model->Draw(glFunctions);
}
