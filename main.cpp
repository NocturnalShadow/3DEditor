#include "display.h"

#include <QFile>
#include <QDebug>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Display display;
    display.show();

    return a.exec();
}
