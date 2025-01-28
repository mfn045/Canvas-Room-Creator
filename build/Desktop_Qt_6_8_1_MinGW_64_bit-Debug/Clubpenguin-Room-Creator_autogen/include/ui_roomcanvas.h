/********************************************************************************
** Form generated from reading UI file 'roomcanvas.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMCANVAS_H
#define UI_ROOMCANVAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomCanvas
{
public:
    QAction *infoAction;
    QAction *editDimensionsAction;
    QAction *actionMove_Selected;
    QAction *actionImport_Sprite;
    QAction *actionRemove_Selected;
    QAction *actionRename_Item;
    QAction *actionAdd_child_sprite_file_to_selected;
    QAction *actionScale_Selected;
    QAction *actionObject_Properties;
    QAction *actionSet_origin;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RoomCanvas)
    {
        if (RoomCanvas->objectName().isEmpty())
            RoomCanvas->setObjectName("RoomCanvas");
        RoomCanvas->resize(800, 600);
        infoAction = new QAction(RoomCanvas);
        infoAction->setObjectName("infoAction");
        editDimensionsAction = new QAction(RoomCanvas);
        editDimensionsAction->setObjectName("editDimensionsAction");
        actionMove_Selected = new QAction(RoomCanvas);
        actionMove_Selected->setObjectName("actionMove_Selected");
        actionImport_Sprite = new QAction(RoomCanvas);
        actionImport_Sprite->setObjectName("actionImport_Sprite");
        actionRemove_Selected = new QAction(RoomCanvas);
        actionRemove_Selected->setObjectName("actionRemove_Selected");
        actionRemove_Selected->setMenuRole(QAction::TextHeuristicRole);
        actionRename_Item = new QAction(RoomCanvas);
        actionRename_Item->setObjectName("actionRename_Item");
        actionAdd_child_sprite_file_to_selected = new QAction(RoomCanvas);
        actionAdd_child_sprite_file_to_selected->setObjectName("actionAdd_child_sprite_file_to_selected");
        actionAdd_child_sprite_file_to_selected->setMenuRole(QAction::NoRole);
        actionScale_Selected = new QAction(RoomCanvas);
        actionScale_Selected->setObjectName("actionScale_Selected");
        actionObject_Properties = new QAction(RoomCanvas);
        actionObject_Properties->setObjectName("actionObject_Properties");
        actionObject_Properties->setMenuRole(QAction::NoRole);
        actionSet_origin = new QAction(RoomCanvas);
        actionSet_origin->setObjectName("actionSet_origin");
        actionSet_origin->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(RoomCanvas);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        RoomCanvas->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RoomCanvas);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName("fileMenu");
        editMenu = new QMenu(menubar);
        editMenu->setObjectName("editMenu");
        RoomCanvas->setMenuBar(menubar);
        statusbar = new QStatusBar(RoomCanvas);
        statusbar->setObjectName("statusbar");
        RoomCanvas->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(editMenu->menuAction());
        fileMenu->addAction(infoAction);
        fileMenu->addAction(actionImport_Sprite);
        editMenu->addAction(editDimensionsAction);
        editMenu->addAction(actionMove_Selected);
        editMenu->addAction(actionRename_Item);
        editMenu->addAction(actionRemove_Selected);
        editMenu->addAction(actionScale_Selected);

        retranslateUi(RoomCanvas);

        QMetaObject::connectSlotsByName(RoomCanvas);
    } // setupUi

    void retranslateUi(QMainWindow *RoomCanvas)
    {
        RoomCanvas->setWindowTitle(QCoreApplication::translate("RoomCanvas", "RoomCanvas", nullptr));
        infoAction->setText(QCoreApplication::translate("RoomCanvas", "Info", nullptr));
        editDimensionsAction->setText(QCoreApplication::translate("RoomCanvas", "Canvas Dimensions", nullptr));
        actionMove_Selected->setText(QCoreApplication::translate("RoomCanvas", "Move Selected", nullptr));
        actionImport_Sprite->setText(QCoreApplication::translate("RoomCanvas", "Import Sprite", nullptr));
        actionRemove_Selected->setText(QCoreApplication::translate("RoomCanvas", "Remove Selected", nullptr));
        actionRename_Item->setText(QCoreApplication::translate("RoomCanvas", "Rename Selected", nullptr));
        actionAdd_child_sprite_file_to_selected->setText(QCoreApplication::translate("RoomCanvas", "Add child sprite to selected", nullptr));
        actionScale_Selected->setText(QCoreApplication::translate("RoomCanvas", "Scale Selected", nullptr));
        actionObject_Properties->setText(QCoreApplication::translate("RoomCanvas", "Object Properties", nullptr));
        actionSet_origin->setText(QCoreApplication::translate("RoomCanvas", "Set origin", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("RoomCanvas", "File", nullptr));
        editMenu->setTitle(QCoreApplication::translate("RoomCanvas", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomCanvas: public Ui_RoomCanvas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMCANVAS_H
