#pragma once

#include "model.h"
#include "entity.h"
#include "drawable.h"


class UserInterfaceItem : public IDrawable, public IEntity
{
private:
    std::unique_ptr<IModel> model;
    Transformation transformation;
    ShaderProgram* program;

    bool isVisible = false;

public:
    UserInterfaceItem() = default;
    UserInterfaceItem(IModel&& _model);
    UserInterfaceItem(UserInterfaceItem&& item);
    UserInterfaceItem(const UserInterfaceItem& item);
    UserInterfaceItem(const IModel& _model, ShaderProgram* _program = nullptr);

    ~UserInterfaceItem() override
    {   }

    UserInterfaceItem& operator=(const UserInterfaceItem& item);

public:
    void Show() { isVisible = true;  }
    void Hide() { isVisible = false; }

    Transformation& Transform() { return transformation; }

    void BindShaderProgram(ShaderProgram* _program) override;
    void Draw(QOpenGLFunctions_4_3_Core* glFunctions) override;
    void Draw(QOpenGLFunctions* glFunctions) override;
};
