#include "display.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

#include "mesh.h"
#include "model.h"

#include <QMatrix4x4>
#include <QQuaternion>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFile f("basicShader.vs");
//    qDebug() << f.exists() << endl;
    QQuaternion q;
    q = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 45.0f);
    QVector3D vec{ 1.0f, 0.0f, 0.0f};
    auto m2 = QMatrix4x4(q.toRotationMatrix()) * QMatrix4x4(q.toRotationMatrix());
    //qDebug() << m1 << m2;
    Scene w;
    w.show();
    return a.exec();
}
