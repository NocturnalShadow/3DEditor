#include "display.h"

Display::Display(QWidget *parent)
    : QWidget(parent), scene(this)
{
    scene.show();
    scene.update();
    scene.grabKeyboard();
}

Display::~Display()
{

}

void Display::AddCube()
{
    std::vector<QVector3D> vertices =
    {
        {-1.0,-1.0,1.0},
        {-1.0,1.0,1.0},
        { 1.0,1.0,1.0},
        { 1.0,-1.0,1.0},
        {-1.0,-1.0,-1.0},
        {-1.0,1.0,-1.0},
        { 1.0,1.0,-1.0},
        { 1.0,-1.0,-1.0},
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
    ColoredModel model(vertices, colors, indices);
    auto cube_id = scene.AddItem(SceneItem(model));
}

void Display::resizeEvent(QResizeEvent* event)
{
    scene.resize(width(), height());
    QWidget::resizeEvent(event);
}

