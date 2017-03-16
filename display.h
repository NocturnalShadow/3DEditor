#pragma once

#include "scene.h"

#include <QWidget>

class Display : public QWidget
{
    Q_OBJECT
private:
    Scene scene;

public:
    Display(QWidget *parent = 0);
    ~Display();
};

