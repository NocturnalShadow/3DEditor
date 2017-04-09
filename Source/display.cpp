#include "display.h"
#include "ui_display.h"
#include "model_loader.h"


Display::Display(QWidget *parent)
    : QWidget(parent), ui{ new Ui::Display },
      file_model{ new QFileSystemModel(this) },
      color_picker{ new QColorDialog(this) },
      material_view_scene{ new QGraphicsScene(this) }
{
    file_model->setRootPath("C:/");

    ui->setupUi(this);

    ui->scene->grabKeyboard();

    ui->treeView->setModel(file_model);
    ui->treeView->setRootIndex(file_model->index("Assets/"));
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(3);

    ui->materialView->setScene(material_view_scene);
    ui->materialView->show();
}

Display::~Display()
{
    delete ui;
}


void Display::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}


void Display::on_treeView_clicked(const QModelIndex& index)
{
    item_path = file_model->fileInfo(index).absoluteFilePath();
}

void Display::on_addItemButton_clicked()
{
    if(auto item_data = ModelLoader::LoadModel(item_path.toStdString()))
    {
        ui->scene->makeCurrent();
        auto item_id = ui->scene->AddItem(SceneItem(*item_data->toColoredModel()));
    }
}

void Display::on_pickMaterialButton_clicked()
{
    if(auto selected_item = ui->scene->SelectedItem())
    {
        auto color = QColorDialog::getColor(Qt::white, this, "Model material");
        ui->materialView->setBackgroundBrush(color);
        selected_item->toColoredModel()->SetColor(color);
    }
}
