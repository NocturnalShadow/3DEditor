/********************************************************************************
** Form generated from reading UI file 'display.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "scene.h"

QT_BEGIN_NAMESPACE

class Ui_Display
{
public:
    QHBoxLayout *horizontalLayout;
    Scene *scene;
    QVBoxLayout *verticalLayout;
    QGraphicsView *materialView;
    QPushButton *pickMaterialButton;
    QSpacerItem *verticalSpacer;
    QTreeView *treeView;
    QPushButton *addItemButton;

    void setupUi(QWidget *Display)
    {
        if (Display->objectName().isEmpty())
            Display->setObjectName(QStringLiteral("Display"));
        Display->resize(1366, 720);
        Display->setMinimumSize(QSize(1280, 720));
        Display->setBaseSize(QSize(1280, 720));
        horizontalLayout = new QHBoxLayout(Display);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scene = new Scene(Display);
        scene->setObjectName(QStringLiteral("scene"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scene->sizePolicy().hasHeightForWidth());
        scene->setSizePolicy(sizePolicy);
        scene->setMinimumSize(QSize(800, 600));
        scene->setCursor(QCursor(Qt::ArrowCursor));
        scene->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(scene);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(5, -1, 5, -1);
        materialView = new QGraphicsView(Display);
        materialView->setObjectName(QStringLiteral("materialView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(materialView->sizePolicy().hasHeightForWidth());
        materialView->setSizePolicy(sizePolicy1);
        materialView->setMinimumSize(QSize(256, 192));

        verticalLayout->addWidget(materialView);

        pickMaterialButton = new QPushButton(Display);
        pickMaterialButton->setObjectName(QStringLiteral("pickMaterialButton"));

        verticalLayout->addWidget(pickMaterialButton);

        verticalSpacer = new QSpacerItem(254, 98, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        treeView = new QTreeView(Display);
        treeView->setObjectName(QStringLiteral("treeView"));
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        treeView->setMinimumSize(QSize(256, 192));
        treeView->setMaximumSize(QSize(256, 192));
        treeView->setBaseSize(QSize(360, 192));
        treeView->setAnimated(true);

        verticalLayout->addWidget(treeView);

        addItemButton = new QPushButton(Display);
        addItemButton->setObjectName(QStringLiteral("addItemButton"));
        sizePolicy1.setHeightForWidth(addItemButton->sizePolicy().hasHeightForWidth());
        addItemButton->setSizePolicy(sizePolicy1);
        addItemButton->setMaximumSize(QSize(256, 16777215));

        verticalLayout->addWidget(addItemButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Display);

        QMetaObject::connectSlotsByName(Display);
    } // setupUi

    void retranslateUi(QWidget *Display)
    {
        Display->setWindowTitle(QApplication::translate("Display", "Form", Q_NULLPTR));
        pickMaterialButton->setText(QApplication::translate("Display", "Pick Material", Q_NULLPTR));
        addItemButton->setText(QApplication::translate("Display", "Add Item", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Display: public Ui_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
