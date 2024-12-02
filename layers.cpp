#include "layers.h"

Layers::Layers(QWidget* parent) {
    setAcceptDrops(true);
    setDragDropMode(DragDrop);
    setDragDropOverwriteMode(true);
    setDefaultDropAction(Qt::MoveAction);

    setHeaderHidden(false);
    setHeaderLabels(QStringList() << "Icon" << "Layer Name");

    setColumnCount(2);
    setMaximumWidth(250);
    setMinimumWidth(250);
}


void Layers::dropEvent(QDropEvent *event){
    emit dropped();
    return QTreeWidget::dropEvent(event);
}
