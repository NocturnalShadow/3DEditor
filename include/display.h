#pragma once

#include "scene.h"

#include <QWidget>
#include <QColorDialog>
#include <QGraphicsScene>
#include <QFileSystemModel>

namespace Ui {
class Display;
}

class Display : public QWidget
{
    Q_OBJECT
private:
    Ui::Display* ui;
    QColorDialog* color_picker;
    QFileSystemModel* file_model;
    QGraphicsScene* material_view_scene;
    QString item_path;

public:
    Display(QWidget *parent = 0);
    ~Display();

public:
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_treeView_clicked(const QModelIndex& index);
    void on_addItemButton_clicked();
    void on_pickMaterialButton_clicked();
};


