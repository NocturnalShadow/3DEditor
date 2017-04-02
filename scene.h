#pragma once

#include "gl_debug.h"

#include "model.h"
#include "camera.h"
#include "shader_program.h"

#include "ui_item.h"
#include "scene_view.h"
#include "scene_item.h"
#include "scene_model.h"

#include "input_manager.h"

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
    std::unique_ptr<SceneModel>     scene_model     = nullptr;
    std::unique_ptr<SceneView>      scene_view      = nullptr;
    std::unique_ptr<InputManager>   input_manager   = nullptr;

    QPoint prev_mouse_pos;
    QPoint mouse_pos_delta;

public:
    Scene(QWidget *parent = nullptr);
    ~Scene() = default;

protected:
    void initializeGL() override;
    void resizeGL(int width, int height);
    void paintGL() override;

public:
    void AddItem(uint item_id, const SceneItem& item);
    void AddItem(uint item_id, SceneItem&& item);

    void AddUserInterfaceItem(uint item_id, const UserInterfaceItem& item);
    void AddUserInterfaceItem(uint item_id, UserInterfaceItem&& item);

    void just_a_test();

public:
    void mousePressEvent(QMouseEvent* event)
    {
        makeCurrent();
        prev_mouse_pos = event->pos();
        scene_view->Camera()->ReverseIfNeeded();
        input_manager->ItemID(event->pos());
    }

    void mouseMoveEvent(QMouseEvent* event)
    {
       mouse_pos_delta = event->pos() - prev_mouse_pos;
       prev_mouse_pos = event->pos();
       if(event->buttons() == Qt::MidButton)
       {
           scene_view->Camera()->Rotate(mouse_pos_delta);
           prev_mouse_pos = event->pos();
       }
    }
    void keyPressEvent(QKeyEvent* event)
    {
        if(event->key() == Qt::Key_R) {
             scene_view->Camera()->Reset();
        }
    }

    void wheelEvent(QWheelEvent* event)
    {
        float delta = event->delta() / 600.0f;
        scene_view->Camera()->Zoom(delta);
    }

};

