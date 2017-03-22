#pragma once

#include "camera.h"
#include "shader_program.h"
#include "model.h"
#include "scene_item.h"

#include <map>
#include <utility>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>

class Scene : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core
{
private:
    Camera camera;
    ShaderProgram program;
    std::map<std::string, SceneItem> items;

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height);
    void paintGL() override;

private:
    void just_a_test();

public:
    void add_item(const std::string& item_name, const SceneItem& item)
    {
        items.emplace(std::make_pair(item_name, item));
        items[item_name].BindShaderProgram(&program);
    }
    void add_item(const std::string& item_name, SceneItem&& item)
    {
        items.emplace(std::make_pair(item_name, std::move(item)));
        items[item_name].BindShaderProgram(&program);
    }
};

