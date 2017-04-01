#pragma once

#include "model.h"
#include "drawable.h"


class UserInterfaceItem : public IDrawable
{
private:
    std::unique_ptr<IModel> model;
    Transformation transformation;
    ShaderProgram* program;

    bool isVisible = false;

public:
    UserInterfaceItem() = default;
    UserInterfaceItem(IModel&& _model)
        : model{ _model.Move() }
    {
        if(!model->isInitialized()) {
            model->InitializeModel();
        }
    }
    UserInterfaceItem(UserInterfaceItem&& item)
        : model{ item.model->Move() },
          transformation{ std::move(item.transformation) },
          program{ std::move(item.program) },
          isVisible{ item.isVisible }
    {

    }
    UserInterfaceItem(const UserInterfaceItem& item)
        : model{ item.model->Clone() },
          transformation{ item.transformation },
          program{ item.program },
          isVisible{ item.isVisible }
    {
        model->InitializeModel();
    }
    UserInterfaceItem(const IModel& _model, ShaderProgram* _program = nullptr)
        : model{ _model.Clone() },
          program{ _program }
    {
        model->InitializeModel();
    }

    UserInterfaceItem& operator=(const UserInterfaceItem& item)
    {
        model.reset(item.model->Clone());
        transformation = item.transformation;
        program = item.program;
        isVisible = item.isVisible;
        model->InitializeModel();
        return *this;
    }

public:
    void Show() { isVisible = true;  }
    void Hide() { isVisible = false; }

    Transformation& Transform() { return transformation; }

    void BindShaderProgram(ShaderProgram* _program) override
    {
        program = _program;
        model->BindShaderProgram(program->Get());
    }
    void Draw(QOpenGLFunctions_4_3_Core* view) override
    {
        if(isVisible)
        {
            program->Update(transformation);
            model->Draw(view);
        }
    }
    void Draw(QOpenGLFunctions* view) override
    {
        if(isVisible)
        {
            program->Update(transformation);
            model->Draw(view);
        }
    }
};
