#pragma once

#include "gl_debug.h"

#include "camera.h"
#include "shader_program.h"
#include "model.h"

#include "scene_model.h"
#include "scene_view.h"
#include "scene_item.h"

#include <memory>

#include <QVector2D>
#include <QMouseEvent>
#include <QWheelEvent>
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
    void mouseMoveEvent(QMouseEvent* event)
    {
       static QPoint prev_pos = event->pos();
       QPoint delta = event->pos() - prev_pos;
       if(event->buttons() == Qt::MidButton)
       {
           scene_view->Camera()->Rotate(delta);
           prev_pos = event->pos();
       }
    }
    void wheelEvent(QWheelEvent* event)
    {
        float delta = event->delta() / 600.0f;
        scene_view->Camera()->Zoom(delta);
    }

};

