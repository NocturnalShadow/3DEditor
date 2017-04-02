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
    uint id = 0;
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
    uint Id() const {
        return id;
    }
    bool SetId(uint _id)
    {
        if(id) {
            return false;
        } else {
            id = _id;
        }
        return true;
    }
    Transformation& Transform() {
        return transformation;
    }

    void BindShaderProgram(ShaderProgram* _program) override;

    void Draw(QOpenGLFunctions* glFunctions) override;
    void Draw(QOpenGLFunctions_4_3_Core* glFunctions) override;
};

