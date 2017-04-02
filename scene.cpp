#include "scene.h"
#include "scene_item.h"
#include "camera.h"

#include <QTimer>
#include <QVector4D>
#include <QVector3D>


Scene::Scene(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(8);
    setFormat(format);

    setMinimumSize(1366,768);
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();

    scene_view.reset(new SceneView(this, "basicShader"));
    scene_model.reset(new SceneModel());
    input_manager.reset(new InputManager(this, context()));

    qDebug((char*)glGetString(GL_VERSION));
    qDebug() << format().version();
    qDebug() << format().profile();

    scene_view->Initialize();
}

void Scene::resizeGL(int width, int height)
{
    scene_view->Resize(width, height);
    input_manager->Resize(width, height);
}

void Scene::paintGL()
{
    just_a_test();

    scene_view->BindShader();
    scene_view->Paint();
    input_manager->Update();

    update();
}

void Scene::AddItem(uint item_id, const SceneItem& item)
{
    SceneItem* item_ptr = new SceneItem(item);
    item_ptr->SetId(item_id);
    scene_model->AddItem(item_id, item_ptr);
    scene_view->AddItem(item_ptr);
}

void Scene::AddItem(uint item_id, SceneItem&& item)
{
    SceneItem* item_ptr = new SceneItem(std::move(item));
    item_ptr->SetId(item_id);
    scene_model->AddItem(item_id, item_ptr);
    scene_view->AddItem(item_ptr);
}

void Scene::AddUserInterfaceItem(uint item_id, const UserInterfaceItem& item)
{
    UserInterfaceItem* item_ptr = new UserInterfaceItem(item);
    scene_model->AddUIItem(item_id, item_ptr);
    scene_view->AddUserInterfaceItem(item_ptr);
}

void Scene::AddUserInterfaceItem(uint item_id, UserInterfaceItem&& item)
{
    UserInterfaceItem* item_ptr = new UserInterfaceItem(std::move(item));
    scene_model->AddUIItem(item_id, item_ptr);
    scene_view->AddUserInterfaceItem(item_ptr);
}


#include "gl_debug.h"

// =====================================================================
// ============== Some temporary visual testing functions ==============
// =====================================================================

void Scene::just_a_test()
{
    static uint frame = 0;
    std::vector<QVector3D> vertices =
    {
        {-1.0,-1.0,1.0},
        {-1.0,1.0,1.0},
        {1.0,1.0,1.0},
        {1.0,-1.0,1.0},
        {-1.0,-1.0,-1.0},
        {-1.0,1.0,-1.0},
        {1.0,1.0,-1.0},
        {1.0,-1.0,-1.0},
    };
    std::vector<uint> indices =
    {
        0, 3, 2,
        0, 2, 1,
        2, 3, 7,
        2, 7, 6,
        0, 4, 7,
        0, 7, 3,
        1, 2, 6,
        1, 6, 5,
        4, 5, 6,
        4, 6, 7,
        0, 1, 5,
        0, 5, 4
    };

    std::vector<QVector4D> colors =
    {
        {0.0, 0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {0.0, 1.0, 1.0, 1.0}
    };

    if(frame == 0)
    {
        ColoredModel model(vertices, colors, indices);
        AddItem(1, SceneItem(model));
        auto ui_item = UserInterfaceItem(model);
        ui_item.Transform().Scale() = QVector3D{0.5f, 0.5f, 0.5f};
        ui_item.Show();
        AddUserInterfaceItem(2, ui_item);
        scene_view->Camera()->MoveTo({0.0f, 0.0f, 8.0f});
    }
      //scene_view->Camera()->Rotate(0, 0.5f);
//    scene_model->Item("TheCube").Transform().Rotation().setY(100.0f * frame / 150);
//    scene_model->Item("TheCube").Transform().SetPosition({0.0f, 0.0f + sin(frame / 60.0f)*2.8f, 4.0f});
//      scene_model->Item("TheCube").Transform().SetPosition({0.0f, 0.0f, 0.0f});
//    static float angle = 0;
//    angle += 0.4f;
//    QMatrix4x4 rotation;
//    rotation.rotate(angle, QVector3D{0.0f, 1.0f, 0.0f});
//    scene_view->Camera()->MoveTo(rotation * QVector3D{0.0f, 0.0f, -8.0f});

//    scene_model->Item("TheCube").Transform().SetPosition({0.0, 2.0, 6.0});
//    scene_view->Paint();
//    scene_model->Item("TheCube").Transform().SetPosition({0.0, -4.0, 6.0});
//    scene_view->Paint();

    frame++;
}
