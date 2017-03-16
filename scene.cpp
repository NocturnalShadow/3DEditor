#include "scene.h"


Scene::Scene(QWidget* parent)
    : QOpenGLWidget(parent), program{"basicShader"}
{
     setMinimumSize(800,600);
}


Scene::~Scene()
{

}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();
    program.InitShader();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

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



// =====================================================================
// ============== Some temporary visual testing functions ==============
// =====================================================================

void Scene::just_a_test()
{
    static GLfloat const square[] =
    {
        -0.5f,  -0.5f,  0.0f,
        -0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    QColor square_color(222, 99, 99, 255);

    static GLfloat const line[] =
    {
         -0.5f,  0.0f,  0.55f,
         0.5f,  0.0f, 0.55f,
        -0.5f,  0.0f,  -0.55f,
        0.5f,  0.0f, -0.55f
    };
    QColor line_color(0, 255, 0, 255);

    static float angle = 0;
    static float posX = 0;
    static float delta = 0.02f;


//              *** Qt datastructures test ***
//  #square
//    QMatrix4x4 model;
//    QMatrix4x4 view;
//    QMatrix4x4 projection;

//    model.translate(0.0f, 0.0f, 3.0f);
//    model.rotate(angle += 0.4f, 1, 0, 0);
//    view.lookAt({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
//    projection.perspective(70.0f, (float) 800 / (float) 600, 0.01f, 25.0f);

//    program.Update(model, view, projection, square_color);


//              *** Transform class test ***
//  #square
    // > Simple translation
    Transform transformation;
    transformation.Position().setZ(3.0f);

    // > Camera move
    if(abs(posX) > 2) delta = -delta;
    camera.SetPosition({posX += delta, 0.0f, 0.0f});

    program.Update(transformation, camera, square_color);

    program.BindData(square);
    glDrawArrays(GL_TRIANGLES, 0, 6);

//  #line
    // > Simple rotation
    transformation.Rotation().setX(angle += 0.7f);

    program.Update(transformation, camera, line_color);

    program.BindData(line);
    glDrawArrays(GL_LINES, 0, 4);
}
