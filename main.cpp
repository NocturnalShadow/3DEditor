#include "display.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f("basicShader.vs");
    qDebug() << f.exists() << endl;
    Scene w;
    w.show();

    return a.exec();
}
