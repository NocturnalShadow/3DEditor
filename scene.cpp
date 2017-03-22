#include "scene.h"
#include "scene_item.h"

Scene::Scene(QWidget* parent)
    : QOpenGLWidget(parent), program{"basicShader"}
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16);
    setFormat(format);

    setMinimumSize(1366,768);
}


Scene::~Scene()
{

}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();
    program.InitShader();

    qDebug((char*)glGetString(GL_VERSION));
    qDebug() << format().version();
    qDebug() << format().profile();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.15f, 0.145f, 0.15f, 1.0f);
}

void Scene::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::paintGL()
{
    just_a_test();
    update();
}


#include "gl_debug.h"

// =====================================================================
// ============== Some temporary visual testing functions ==============
// =====================================================================

void Scene::just_a_test()
{
    static uint frame = 0;
    program.Bind();

//    QMatrix4x4 matrix;
//    matrix.perspective(60.0f, 16.0f/9.0f, 1.0f, 100.0f);
//    matrix.lookAt({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
//    matrix.translate({0.0f, 0.0f, 2.0f});

    camera.MoveTo({0.0f, 0.0f, -4.5f});

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
     Model model(vertices, colors, indices);
     program.Update(camera);

    if(frame == 0)
    {
        Model model(vertices, colors, indices);
        add_item("TheCube", SceneItem(model));
    }
    program.Update(camera);
    glViewport(0, 0, 1366, 768);

    items["TheCube"].Transform().Rotation().setY(100.0f * frame / 150);
    items["TheCube"].Transform().SetPosition({0.0, 0.0, 2.0});
    items["TheCube"].Draw(this);
    items["TheCube"].Transform().SetPosition({0.0, 2.0, 2.0});
    items["TheCube"].Draw(this);
    items["TheCube"].Transform().SetPosition({0.0, -2.0, 2.0});
    items["TheCube"].Draw(this);

    frame++;
}
