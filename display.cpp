#include "display.h"

Display::Display(QWidget *parent)
    : QWidget(parent), scene(this)
{
    scene.show();
    scene.update();
}

Display::~Display()
{

}
