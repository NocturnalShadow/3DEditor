#include "scene.h"


Scene::Scene(QWidget* parent)
    : QOpenGLWidget(parent), program{"basicShader"}
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16);
    setFormat(format);

    setMinimumSize(800,600);
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
    Transform transformation;
    transformation.Position().setZ(2);
    transformation.Rotation().setY(100.0f * frame / 150);

    program.Bind();

    //QMatrix4x4 matrix;
    //matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.lookAt({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
    //matrix.translate({0.0f, 0.0f, 2.0f});
    //matrix *= transformation.Model();
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    camera.MoveTo({0.0f, 2.0f, -1.5f});
    camera.LookAt({0.0f, 1.0f, 0.0f});
    //program.Update(matrix);
    program.Update(transformation, camera);

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
         {0.0,0.0,0.0, 0.0},
         {1.0,0.0,0.0, 0.0},
         {1.0,1.0,0.0, 0.0},
         {0.0,1.0,0.0, 0.0},
         {0.0,0.0,1.0, 0.0},
         {1.0,0.0,1.0, 0.0},
         {1.0,1.0,1.0, 0.0},
         {0.0,1.0,1.0, 0.0},
     };

    Model model(vertices, colors, indices);

    model.BindShaderProgram(program.Get());
    model.Draw(this);
    frame++;
}
