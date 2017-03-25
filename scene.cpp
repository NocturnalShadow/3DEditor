#include "scene.h"
#include "scene_item.h"
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

Scene::Scene(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16);
    setFormat(format);

    setMinimumSize(1366,768);
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();

    scene_view.reset(new SceneView(this, "basicShader"));
    scene_model.reset(new SceneModel());

    qDebug((char*)glGetString(GL_VERSION));
    qDebug() << format().version();
    qDebug() << format().profile();

    scene_view->Initialize();
}

void Scene::resizeGL(int width, int height)
{
    scene_view->Resize(width, height);
}

void Scene::paintGL()
{
    scene_view->BindShader();
    just_a_test();
    update();
}

void Scene::AddItem(const std::string &item_name, const SceneItem &item)
{
    SceneItem* item_ptr = new SceneItem(item);
    scene_view->AddItem(item_ptr);
    scene_model->AddItem(item_name, item_ptr);
}

void Scene::AddItem(const std::string &item_name, SceneItem &&item)
{
    SceneItem* item_ptr = new SceneItem(std::move(item));
    scene_view->AddItem(item_ptr);
    scene_model->AddItem(item_name, item_ptr);
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
        {0.0, 0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0, 0.0},
        {1.0, 1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {1.0, 0.0, 1.0, 0.0},
        {1.0, 1.0, 1.0, 0.0},
        {0.0, 1.0, 1.0, 0.0}
    };

    if(frame == 0)
    {
        Model model(vertices, colors, indices);
        auto scene_item = SceneItem(model);
        AddItem("TheCube", scene_item);
        scene_view->Camera()->MoveTo({3.0f, 0.0f, -6.0f});

        // Some debugging trying to figure out
        // why glm and Qt give differrent results for perspective matrix
        QMatrix4x4 qPerspective;
        qPerspective.setToIdentity();
        qDebug() << "Perspectives";
        qDebug() << "Qt";
        qPerspective.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);                             // the same !!!
        qPerspective = qPerspective.transposed();
        for(int i = 0; i < 4; ++i)
                qDebug() << qPerspective.row(i)[0] << " " << qPerspective.row(i)[1]
                         << " " << qPerspective.row(i)[2] << " " << qPerspective.row(i)[3]      //     ||
                         << endl;
        qDebug() << "GLM";
        glm::mat4 glmPerspective = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);          // the same !!!
        for(int i = 0; i < 4; ++i)
                qDebug() << glmPerspective[i][0] << " " << glmPerspective[i][1]
                         << " " << glmPerspective[i][2] << " " << glmPerspective[i][3] << endl;

        qDebug() << "Views";
        qDebug() << "Qt";
        QMatrix4x4 qView;
        qView.setToIdentity();
        qView.lookAt({3.0f, 0.0f, -6.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
        qView = qView.transposed();
        for(int i = 0; i < 4; ++i)
                qDebug() << qView.row(i)[0] << " " << qView.row(i)[1] << " " << qView.row(i)[2] << " " << qView.row(i)[3];
        qDebug() << "GLM";
        glm::mat4 glmView = glm::lookAt(glm::vec3{3.0f, 0.0f, -6.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f});
        for(int i = 0; i < 4; ++i)
                qDebug() << glmView[i][0] << " " << glmView[i][1] << " " << glmView[i][2] << " " << glmView[i][3];
    }
if(frame < 70){
    scene_model->Item("TheCube").Transform().Rotation().setY(100.0f * frame / 150);
    scene_model->Item("TheCube").Transform().SetPosition({0.0f, 0.0f, 0.0f + sin(frame / 60.0f)*2.5f});
}
    scene_view->Paint();

//    scene_model->Item("TheCube").Transform().SetPosition({0.0, 2.0, 6.0});
//    scene_view->Paint();
//    scene_model->Item("TheCube").Transform().SetPosition({0.0, -4.0, 6.0});
//    scene_view->Paint();

    frame++;
}
