#include "display.h"

#include <QApplication>
#include <QFile>
#include <QDebug>


#include <QMatrix4x4>
#include <QQuaternion>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Display dispaly;
    dispaly.show();
    dispaly.AddCube();

    return a.exec();
}
