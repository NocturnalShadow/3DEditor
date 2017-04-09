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
    format.setStencilBufferSize(16);
    setFormat(format);

    //setMinimumSize(1366,768);
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();

    scene_view.reset(new SceneView(this, ":/Shaders/common_shader"));
    scene_model.reset(new SceneModel());
    input_manager.reset(new InputManager(this, context()));
    entity_manager.reset(new EntityManager());

    qDebug((char*)glGetString(GL_VERSION));
    qDebug() << format().version();
    qDebug() << format().profile();

    scene_view->Initialize();

    GenerateUI();
    GenerateGrid(8);
}

void Scene::resizeGL(int width, int height)
{
    scene_view->Resize(width, height);
    input_manager->Resize(width, height);
}

void Scene::paintGL()
{
    scene_view->BindShader();
    scene_view->Paint();
    input_manager->Update();

    update();
}

uint Scene::AddItem(const SceneItem& item)
{
    SceneItem* item_ptr = new SceneItem(item);
    uint item_id = 0;
    if(!(item_id = AddItem(item_ptr))){
        delete item_ptr;
    }
    return item_id;
}

uint Scene::AddItem(SceneItem&& item)
{
    SceneItem* item_ptr = new SceneItem(std::move(item));
    uint item_id = 0;
    if(!(item_id = AddItem(item_ptr))){
        delete item_ptr;
    }
    return item_id;
}

uint Scene::AddItem(SceneItem* item)
{
    uint item_id = 0;
    if(item && (item_id = entity_manager->AddItem(item)))
    {
        scene_model->AddItem(item);
        scene_view->AddItem(item);
    }
    return item_id;
}

SceneViewCamera* Scene::Camera()
{
    return scene_view->Camera();
}

SceneItem* Scene::Item(uint id)
{
    return dynamic_cast<SceneItem*>(entity_manager->Item(id));
}

SceneItem* Scene::SelectedItem()
{
    return selected_item;
}

uint Scene::AddUserInterfaceItem(const UserInterfaceItem& item)
{
    UserInterfaceItem* item_ptr = new UserInterfaceItem(item);

    scene_model->AddUIItem(item_ptr);
    scene_view->AddUserInterfaceItem(item_ptr);
    return entity_manager->AddItem(item_ptr);
}

uint Scene::AddUserInterfaceItem(UserInterfaceItem&& item)
{
    UserInterfaceItem* item_ptr = new UserInterfaceItem(std::move(item));

    scene_model->AddUIItem(item_ptr);
    scene_view->AddUserInterfaceItem(item_ptr);
    return entity_manager->AddItem(item_ptr);
}

void Scene::GenerateUI()
{
    std::vector<QVector3D> vertices =
    {
        {-1.0, -1.0,  1.0 },
        {-1.0,  1.0,  1.0 },
        { 1.0,  1.0,  1.0 },
        { 1.0, -1.0,  1.0 },
        {-1.0, -1.0, -1.0 },
        {-1.0,  1.0, -1.0 },
        { 1.0,  1.0, -1.0 },
        { 1.0, -1.0, -1.0 },
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

    ColoredModel model(vertices, indices);

    model.SetColor(Qt::white);
    UserInterfaceItem center = UserInterfaceItem(model);
    center.Transform().SetScale({0.046f, 0.046f, 0.046f});
    AddUserInterfaceItem(center);
    ui_items[AddUserInterfaceItem(center)] = UI::CENTER;

    model.SetColor(QVector4D{1.0f, 0.0f, 0.0f, 0.67f});
    UserInterfaceItem x_axis = UserInterfaceItem(model);
    x_axis.Transform().SetScale({0.5f, 0.025f, 0.025f});
    x_axis.Transform().SetPosition({0.5, 0.0, 0.0});
    ui_items[AddUserInterfaceItem(x_axis)] = UI::X_AXIS;

    model.SetColor(QVector4D{0.0f, 1.0f, 0.0f, 0.67f});
    UserInterfaceItem y_axis = UserInterfaceItem(model);
    y_axis.Transform().SetScale({0.5f, 0.025f, 0.025f});
    y_axis.Transform().SetRotation({0.0f, 0.0f, 90.0f});
    y_axis.Transform().SetPosition({0.0, 0.5, 0.0});
    ui_items[AddUserInterfaceItem(y_axis)] = UI::Y_AXIS;

    model.SetColor(QVector4D{0.0f, 0.0f, 1.0f, 0.67f});
    UserInterfaceItem z_axis = UserInterfaceItem(model);
    z_axis.Transform().SetScale({0.5f, 0.025f, 0.025f});
    z_axis.Transform().SetRotation({0.0f, -90.0f, 0.0f});
    z_axis.Transform().SetPosition({0.0, 0.0, 0.5});
    ui_items[AddUserInterfaceItem(z_axis)] = UI::Z_AXIS;
}

void Scene::BindUI()
{
    for(const auto& item : ui_items)
    {
        auto ui_item = dynamic_cast<UserInterfaceItem*>(entity_manager->Item(item.first));
        ui_item->BindLocation(selected_item->Transform().Position());
        ui_item->Show();
    }
}

void Scene::ReleaseUI()
{
    for(const auto& item : ui_items)
    {
        auto ui_item = dynamic_cast<UserInterfaceItem*>(entity_manager->Item(item.first));
        ui_item->Hide();
    }
}

void Scene::GenerateGrid(int size)
{
    std::vector<QVector3D> vertices;
    for(int i = 0; i <= size; ++i)
    {
        vertices.push_back({ size  / 2.0f,     0.0f,   size / 2.0f - i});
        vertices.push_back({-size  / 2.0f,     0.0f,   size / 2.0f - i});
        vertices.push_back({ size  / 2.0f - i, 0.0f,   size / 2.0f    });
        vertices.push_back({ size  / 2.0f - i, 0.0f,  -size / 2.0f    });
    }

    ColoredModel grid(vertices, QVector4D{1.0, 1.0, 1.0, 1.0});
    grid.ResetNormals();
    auto grid_id = AddItem(SceneItem(grid));
    dynamic_cast<SceneItem*>(entity_manager->Item(grid_id))->SetPrimitive(GL_LINES);
}

void Scene::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    prev_mouse_pos = event->pos();
    scene_view->Camera()->ReverseIfNeeded();

    if(event->button() == Qt::LeftButton)
    {
        auto item_id = input_manager->ItemID(event->pos());
        if(item_id != 0)
        {
            auto item = entity_manager->Item(item_id);
            if(auto scene_item = dynamic_cast<SceneItem*>(item))
            {
                selected_item = scene_item;
                BindUI();
            } else {
                ui = ui_items[item_id];
            }
        } else {
            ReleaseUI();
            ui = UI::CENTER;
            selected_item = nullptr;
        }
    }
}

void Scene::mouseMoveEvent(QMouseEvent* event)
{
    mouse_pos_delta = event->pos() - prev_mouse_pos;
    prev_mouse_pos = event->pos();
    auto buttons = event->buttons();
    auto mods = event->modifiers();
    if(buttons == Qt::MidButton)
    {
        scene_view->Camera()->Rotate(mouse_pos_delta);
        prev_mouse_pos = event->pos();
    }
    else if(buttons == Qt::LeftButton)
    {
        if(!selected_item) return;

        mouse_pos_delta.ry() = -mouse_pos_delta.ry();

        QVector3D screen_axis{ };

        float x_value = 0;
        float y_value = 0;
        float z_value = 0;

        QVector2D x_projection;
        QVector2D y_projection;
        QVector2D z_projection;

        switch(ui)
        {
            case UI::X_AXIS:
                screen_axis = QVector3D((scene_view->Camera()->ViewProjection() * QVector4D{1.0f, 0.0f, 0.0f, 1.0f}).normalized());
                x_value = QVector2D::dotProduct(QVector2D(mouse_pos_delta), QVector2D(screen_axis));
                if(mode == Mode::ROTATE) {
                    x_projection =  QVector2D(mouse_pos_delta) - QVector2D(screen_axis * x_value);
                }
                break;
            case UI::Y_AXIS:
                screen_axis = QVector3D((scene_view->Camera()->ViewProjection() * QVector4D{0.0f, 1.0f, 0.0f, 1.0f}).normalized());
                y_value = QVector2D::dotProduct(QVector2D(mouse_pos_delta), QVector2D(screen_axis));
                if(mode == Mode::ROTATE) {
                    y_projection =  QVector2D(mouse_pos_delta) - QVector2D(screen_axis * y_value);
                }
                break;
            case UI::Z_AXIS:
                screen_axis = QVector3D((scene_view->Camera()->ViewProjection() * QVector4D{0.0f, 0.0f, 1.0f, 1.0f}).normalized());
                z_value = QVector2D::dotProduct(QVector2D(mouse_pos_delta), QVector2D(screen_axis));
                if(mode == Mode::ROTATE) {
                    z_projection =  QVector2D(mouse_pos_delta) - QVector2D(screen_axis * z_value);
                }
                break;
        }
        if(mods == Qt::CTRL){
            x_value = y_value = z_value = (x_value ? x_value : (y_value ? y_value : z_value));
        }
        switch(mode)
        {
            case Mode::MOVE:
            {
                selected_item->Transform().IncPosition({sensitivity * x_value / 15.0f, 0.0f, 0.0f});
                selected_item->Transform().IncPosition({0.0f, sensitivity * y_value / 15.0f, 0.0f});
                selected_item->Transform().IncPosition({0.0f, 0.0f, sensitivity * z_value / 15.0f});
                break;
            }
            case Mode::ROTATE:
            {
                selected_item->Transform().AddRotation({-sgn(screen_axis.x()) * sgn(x_projection.y()) * x_projection.length(), 0.0f, 0.0f});
                selected_item->Transform().AddRotation({0.0f,  sgn(screen_axis.y()) * sgn(y_projection.x()) * y_projection.length(), 0.0f});
                selected_item->Transform().AddRotation({0.0f, 0.0f, -sgn(screen_axis.x()) * sgn(z_projection.y()) * z_projection.length() * z_projection.length() / 6.0f});
                break;
            }
            case Mode::SCALE:
            {
                selected_item->Transform().IncScale({x_value / 8.0f, 0.0f, 0.0f});
                selected_item->Transform().IncScale({0.0f, y_value / 8.0f, 0.0f});
                selected_item->Transform().IncScale({0.0f, 0.0f, z_value / 8.0f});
                break;
            }
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R) {
        scene_view->Camera()->Reset();
    }
    if(event->key() == Qt::Key_Q) {
        mode = Mode::MOVE;
    }
    if(event->key() == Qt::Key_W) {
        mode = Mode::ROTATE;
    }
    if(event->key() == Qt::Key_E) {
        mode = Mode::SCALE;
    }
}

void Scene::wheelEvent(QWheelEvent *event)
{
    float delta = event->delta() / 690.0f;
    sensitivity -= delta;
    scene_view->Camera()->Zoom(delta);
}
