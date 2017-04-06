#pragma once

#include "gl_debug.h"
#include "mathematics.h"

#include "model.h"
#include "camera.h"
#include "shader_program.h"

#include "ui_item.h"
#include "scene_view.h"
#include "scene_item.h"
#include "scene_model.h"

#include "entity.h"
#include "input_manager.h"

#include <memory>

#include <QVector2D>
#include <QVector3D>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>


class Scene : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core
{
    enum class UI
    {
        CENTER,
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
    };
    enum class Mode
    {
        MOVE,
        ROTATE,
        SCALE
    };

private:
    std::unique_ptr<SceneModel>     scene_model     = nullptr;
    std::unique_ptr<SceneView>      scene_view      = nullptr;
    std::unique_ptr<InputManager>   input_manager   = nullptr;
    std::unique_ptr<EntityManager>  entity_manager  = nullptr;

    std::map<uint, UI> ui_items;

    QPoint prev_mouse_pos;
    QPoint mouse_pos_delta;

    SceneItem* selected_item                        = nullptr;

    UI ui                                           = UI::CENTER;
    Mode mode                                       = Mode::MOVE;

public:
    Scene(QWidget *parent = nullptr);
    ~Scene() = default;

protected:
    void initializeGL() override;
    void resizeGL(int width, int height);
    void paintGL() override;

public:
    uint AddItem(const SceneItem& item);
    uint AddItem(SceneItem&& item);

    uint AddUserInterfaceItem(const UserInterfaceItem& item);
    uint AddUserInterfaceItem(UserInterfaceItem&& item);

    void GenerateUI();
    void BindUI();
    void ReleaseUI();

    void just_a_test();

public:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);

};

