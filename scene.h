#pragma once

#include "gl_debug.h"

#include "camera.h"
#include "shader_program.h"
#include "model.h"

#include "scene_model.h"
#include "scene_view.h"
#include "scene_item.h"

#include <memory>

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class Scene : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core
{
private:
    std::unique_ptr<SceneModel> scene_model = nullptr;
    std::unique_ptr<SceneView>  scene_view  = nullptr;

public:
    Scene(QWidget *parent = nullptr);
    ~Scene() = default;

protected:
    void initializeGL() override;
    void resizeGL(int width, int height);
    void paintGL() override;

public:
    void AddItem(const std::string& item_name, const SceneItem& item);
    void AddItem(const std::string& item_name, SceneItem&& item);

    void just_a_test();

public:
    void mouseMoveEvent(QMouseEvent* event){
       if(event->buttons() == Qt::MidButton && event->modifiers() == Qt::AltModifier)
           qDebug() << event->pos();
    }
};

