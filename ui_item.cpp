
#include "ui_item.h"


UserInterfaceItem::UserInterfaceItem(IModel&& _model)
    : model{ _model.Move() }
{
    if(!model->isInitialized()) {
        model->InitializeModel();
    }
}

UserInterfaceItem::UserInterfaceItem(UserInterfaceItem&& item)
    : model             { item.model->Move()                },
      transformation    { std::move(item.transformation)    },
      program           { std::move(item.program)           },
      isVisible         { item.isVisible                    }
{
}

UserInterfaceItem::UserInterfaceItem(const UserInterfaceItem& item)
    : model             { item.model->Clone() },
      transformation    { item.transformation },
      program           { item.program        },
      isVisible         { item.isVisible      }
{
    model->InitializeModel();
}

UserInterfaceItem::UserInterfaceItem(const IModel& _model, ShaderProgram* _program)
    : model     { _model.Clone() },
      program   { _program       }
{
    model->InitializeModel();
}

UserInterfaceItem& UserInterfaceItem::operator=(const UserInterfaceItem& item)
{
    model.reset(item.model->Clone());
    model->InitializeModel();

    transformation      = item.transformation;
    program             = item.program;
    isVisible           = item.isVisible;

    return *this;
}

void UserInterfaceItem::BindShaderProgram(ShaderProgram* _program)
{
    program = _program;
    model->BindShaderProgram(program->Get());
}

void UserInterfaceItem::Draw(QOpenGLFunctions_4_3_Core* glFunctions)
{
    glFunctions->glEnable(GL_STENCIL_TEST);
    glFunctions->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glFunctions->glStencilFunc(GL_ALWAYS, Id(), -1);

    if(isVisible)
    {
        QMatrix4x4 matrix;
        if(location != nullptr) {
            matrix.translate(*location);
        }
        program->Update(matrix * transformation.Model());
        model->Draw(glFunctions, primitive);
    }

     glFunctions->glDisable(GL_STENCIL_TEST);
}

void UserInterfaceItem::Draw(QOpenGLFunctions* glFunctions)
{
    glFunctions->glEnable(GL_STENCIL_TEST);
    glFunctions->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glFunctions->glStencilFunc(GL_ALWAYS, Id(), -1);

    if(isVisible)
    {
        QMatrix4x4 matrix;
        if(location != nullptr) {
            matrix.translate(*location);
        }
        program->Update(matrix * transformation.Model());
        model->Draw(glFunctions, primitive);
    }

    glFunctions->glDisable(GL_STENCIL_TEST);
}

void UserInterfaceItem::BindLocation(const QVector3D& _location)
{
    location = &_location;
}

void UserInterfaceItem::ReleaseLocation()
{
    location = nullptr;
}
