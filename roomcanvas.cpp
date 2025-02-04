#include "roomcanvas.h"
#include "./ui_roomcanvas.h"

RoomCanvas::RoomCanvas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RoomCanvas)
{
    ui->setupUi(this);
    ui->centralwidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->centralwidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(QPoint)));

    canvas = new Canvas();

    connect(canvas,&Canvas::canvasDropped,[&](QPointF pos){
        QList<QGraphicsItem*> selected = scene->selectedItems();
        if(selected.size() >= 1){
            for(QGraphicsItem* item : selected){
                MultiCanvasObject* itemObj = (MultiCanvasObject*) item;
                itemObj->getCurrentProperties()->xOffset=item->pos().x()-itemObj->getOrigin().x();
                itemObj->getCurrentProperties()->yOffset=item->pos().y()-itemObj->getOrigin().y();
            }
        }
    });

    ui->centralwidget->layout()->addWidget(canvas);

    layers=new Layers();

    connect(layers,SIGNAL(dropped()),this,SLOT(updateItems()));
    connect(layers,SIGNAL(itemSelectionChanged()),this,SLOT(changeGraphicsSelection()));

    ui->centralwidget->layout()->addWidget(layers);


    scene = new Scene();
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(changeLayersSelection()));

    canvas->setScene(scene);

    thread = QThread::create([this](){
        while(true){
            QMetaObject::invokeMethod(this,"nextFrame", Qt::QueuedConnection);
            QThread::msleep(40);
        }
    });
    thread->start();
}

RoomCanvas::~RoomCanvas()
{
    delete ui;
}


void RoomCanvas::mousePressEvent(QMouseEvent *event){
    if(selectingOrigin != nullptr){
        QPointF pos = canvas->mapFrom(this,event->pos());
        MultiCanvasObject* obj = (MultiCanvasObject*)selectingOrigin;
        obj->setOrigin(pos);
        selectingOrigin = nullptr;
        setCursor(Qt::ArrowCursor);
        canvas->setDisabled(false);
    }
    QWidget::mousePressEvent(event);
}

void RoomCanvas::contextMenuRequested(QPoint point){
    QMenu* menu = new QMenu(this);
    menu->addAction(ui->actionMove_Selected);
    menu->addAction(ui->actionRemove_Selected);
    menu->addAction(ui->actionRename_Item);
    menu->addAction(ui->actionAdd_child_sprite_file_to_selected);
    menu->addAction(ui->actionSet_origin);
    menu->addAction(ui->actionObject_Properties);
    menu->popup(ui->centralwidget->mapToGlobal(point));
}

void checkGraphicsChildSelection(QGraphicsItem* item, QTreeWidgetItem* selectedTreeItem){
    QList<QGraphicsItem*> children = item->childItems();
    if(children.size() >= 1){
        for(QGraphicsItem* child : children){
            MultiCanvasObject* childObj = (MultiCanvasObject*)child;
            for(int i = 0; i < selectedTreeItem->childCount(); i++){
                QTreeWidgetItem* childTreeItem = selectedTreeItem->child(i);
                QString layerID = childTreeItem->text(1);
                if(childObj->isSelected()){
                    if(childObj->getName().isEmpty()){
                        if(layerID.replace("Child ", "").toInt() == childObj->getID()){
                            childTreeItem->setSelected(true);
                        }
                    }else{
                        if(layerID == childObj->getName()){
                            childTreeItem->setSelected(true);
                        }
                    }
                }
                checkGraphicsChildSelection(childObj,childTreeItem);
            }
        }
    }
}

void RoomCanvas::changeLayersSelection(){
    if(scene->items().isEmpty() || updatingSelection) return;
    updatingSelection = true;
    layers->clearSelection();
    for(QGraphicsItem* item : scene->items()){
        MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
        if(obj){
            for(int i = 0; i < layers->invisibleRootItem()->childCount(); i++){
                QTreeWidgetItem* selectedTreeItem = layers->invisibleRootItem()->child(i);
                QString layerID = selectedTreeItem->text(1);
                if(obj->isSelected()){
                    if(obj->getName().isEmpty()){
                        if(layerID.replace("Layer ", "").toInt() == obj->getID()){
                            selectedTreeItem->setSelected(true);
                        }
                    }else{
                        if(layerID == obj->getName()){
                            selectedTreeItem->setSelected(true);
                        }
                    }
                }
                checkGraphicsChildSelection(obj,selectedTreeItem);
            }
        }
    }
    updatingSelection = false;
}

void checkLayersChildSelection(QGraphicsItem* item, QTreeWidgetItem* selectedTreeItem){
    QList<QGraphicsItem*> children = item->childItems();
    if(children.size() >= 1){
        for(QGraphicsItem* child : children){
            MultiCanvasObject* childObj = (MultiCanvasObject*)child;
            for(int i = 0; i < selectedTreeItem->childCount(); i++){
                QTreeWidgetItem* childTreeItem = selectedTreeItem->child(i);
                QString layerID = childTreeItem->text(1);
                if(childTreeItem->isSelected()){
                    if(childObj->getName().isEmpty()){
                        if(layerID.replace("Child ", "").toInt() == childObj->getID()){
                            childObj->setSelected(true);
                        }
                    }else{
                        if(layerID == childObj->getName()){
                            childObj->setSelected(true);
                        }
                    }
                }
                checkLayersChildSelection(childObj,childTreeItem);
            }
        }
    }
}

void RoomCanvas::changeGraphicsSelection(){
    if(scene->items().isEmpty() || updatingSelection) return;
    updatingSelection = true;
    scene->clearSelection();
    for(QGraphicsItem* item : scene->items()){
        MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
        if(obj){
        for(int i = 0; i < layers->invisibleRootItem()->childCount(); i++){
            QTreeWidgetItem* selectedTreeItem = layers->invisibleRootItem()->child(i);
            QString layerID = layers->invisibleRootItem()->child(i)->text(1);
            if(selectedTreeItem->isSelected()){
                if(obj->getName().isEmpty()){
                    if(layerID.replace("Layer ", "").toInt() == obj->getID()){
                        obj->setSelected(true);
                    }
                }else{
                    if(layerID == obj->getName()){
                        obj->setSelected(true);
                    }
                }
            }
            checkLayersChildSelection(obj,selectedTreeItem);
        }
        }
    }
    updatingSelection = false;
}

void RoomCanvas::nextFrame(){
    if(attemptingUpdate) return;
    for(QGraphicsItem* item : scene->items()){
        MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
        if(obj){
            if(!obj->getCurrentFrames().isEmpty() && obj->getCurrentFrames().size() >= 2){
                obj->nextFrame(obj->hasAnimationLoop());
            }
        }
        AtlasCanvasObject* obj2 = dynamic_cast<AtlasCanvasObject*>(item);
        if(obj2){
            if(!obj2->getCurrentSpriteFrames().isEmpty() && obj2->getCurrentSpriteFrames().size() >= 2){
                obj2->nextFrame(obj2->hasAnimationLoop());
            }
        }
    }
}

void updateChildLayers(MultiCanvasObject* obj,QTreeWidgetItem* parent){
    QList<QGraphicsItem*> children = obj->childItems();
    if(children.size() >= 1){
        for(QGraphicsItem* child : children){
            if(auto childObj = dynamic_cast<MultiCanvasObject*>(child)){
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setIcon(0,QIcon(*childObj->getCurrentFrames().at(0)));
            if(obj->getName().isEmpty()){
                item->setText(1,"Child " + QString::number(childObj->getID()));
            }else{
                item->setText(1,childObj->getName());
            }
            item->setFlags(item->flags() ^ Qt::ItemIsDropEnabled);
            parent->addChild(item);
            updateChildLayers(childObj,item);
            }
        }
    }
}

void RoomCanvas::updateLayers(){
    layers->clear();
    for(QGraphicsItem* item : scene->items()){
        MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
        if(obj){
        if(obj->getCurrentFrames().isEmpty()) continue;
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setIcon(0,QIcon(*obj->getCurrentFrames().at(0)));
        if(obj->getName().isEmpty()){
            item->setText(1,"Layer " + QString::number(obj->getID()));
        }else{
            item->setText(1,obj->getName());
        }
        item->setFlags(item->flags() ^ Qt::ItemIsDropEnabled);
        layers->insertTopLevelItem(0,item);
        QList<QGraphicsItem*> children = obj->childItems();
        if(children.size() >= 1){
            updateChildLayers(obj,item);
        }
        }
    }
}

void RoomCanvas::updateItems(){
    if(layers->invisibleRootItem() == nullptr) return;
    attemptingUpdate = true;
    QList<MultiCanvasObject*> updatedItems;
    bool updated = false;
    for(int i = 0; i < layers->invisibleRootItem()->childCount(); i++){
        QTreeWidgetItem* item = layers->invisibleRootItem()->child(i);
        QString layerID = item->text(1);
        for(QGraphicsItem* item : scene->items()){
            MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
            if(obj){
            if(obj->getName().isEmpty()){
                if(layerID.replace("Layer ","").toInt() == obj->getID()){
                    updatedItems.push_front(obj);
                    updated = true;
                }
            }else{
                if(obj->getName() == layerID){
                    updatedItems.push_front(obj);
                    updated = true;
                }
            }
            }
        }
    }
    /*if(updated){
        items = updatedItems;
    }*/
    for(QGraphicsItem* item : scene->items()){
        if(auto obj = dynamic_cast<MultiCanvasObject*>(item)){
        scene->removeItem(item);
        }
    }
    scene->update();
    for(int i = 0; i <= updatedItems.size()-1; i++){
        scene->addItem(updatedItems.at(i));
    }
    scene->update();
    attemptingUpdate = false;
}

/*QList<MultiCanvasObject*>& RoomCanvas::getItems(){
    return this->items;
}*/

Scene* RoomCanvas::getScene(){
    return this->scene;
}

Canvas* RoomCanvas::getCanvas(){
    return this->canvas;
}

void RoomCanvas::addItem(QString dir){
    if(dir.isEmpty()) return;
    MultiCanvasObject* item = new MultiCanvasObject();
    item->setCursor(Qt::PointingHandCursor);
    //items.append(item);
    item->setID(id_increment);
    id_increment++;
    scene->addItem(item);
    updateLayers();
}

void RoomCanvas::remItemByCanvasObject(MultiCanvasObject* canvasObj){
    if(canvasObj == nullptr) return;
    QList<MultiCanvasObject*> updatedItems;
    for(QGraphicsItem* item : scene->items()){
        MultiCanvasObject* obj = dynamic_cast<MultiCanvasObject*>(item);
        if(obj){
        if(obj != canvasObj){
            updatedItems.append(obj);
        }
        }
    }
    scene->removeItem(canvasObj);
    updateLayers();
}

void RoomCanvas::on_importSpriteFile_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this,"Select a sprite file");

    addItem(dir);
}

QString RoomCanvas::getFilePath(){
    QMessageBox mb(this);
    mb.setText("Do you want to select a directory or a file?");
    mb.addButton("File",QMessageBox::NoRole);
    mb.addButton("Directory",QMessageBox::NoRole);
    mb.addButton(QMessageBox::Cancel);
    mb.setDefaultButton(QMessageBox::Cancel);
    mb.exec();
    QUrl directory;
    QString filePath = "";
    if(mb.clickedButton()->text() == "Directory"){
        filePath = QFileDialog::getExistingDirectory(this,"Select a sprite directory");
    } else if(mb.clickedButton()->text() == "File"){
        directory = QFileDialog::getOpenFileUrl(this,"Select a sprite file");
        filePath = directory.toString().replace("file:///","");
    }
    return filePath;
}

void RoomCanvas::on_actionImport_Sprite_triggered()
{
    addItem(getFilePath());
}


void RoomCanvas::on_actionMove_Selected_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Move Item");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    QInputDialog dialog;
    double x = dialog.getDouble(this,"Insert move location","Insert X:",0,-2147483647,2147483647,5);
    double y = dialog.getDouble(this,"Insert move location","Insert Y:",0,-2147483647,2147483647,5);

    for(QGraphicsItem* item : selectedItems){
        item->setPos(x,y);

    }
}


void RoomCanvas::on_editDimensionsAction_triggered()
{
    QInputDialog dialog;
    double width = dialog.getDouble(this,"Insert canvas dimensions","Insert Width:",0,-2147483647,2147483647,5);
    double height = dialog.getDouble(this,"Insert canvas dimensions","Insert Height:",0,-2147483647,2147483647,5);

    QRectF f;
    f.setRect(0,0,width,height);
    //scene->setSceneRect(f);
    scene->setSceneRect(f);
    canvas->setFixedSize(QSize(width+10,height+10));
    //scene->setSceneRect(f);
}


void RoomCanvas::on_actionRemove_Selected_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Remove Item");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    QMessageBox mb(this);
    mb.setText("Are you sure you would like to delete the selected items?");
    mb.addButton(QMessageBox::StandardButton::Yes);
    mb.addButton(QMessageBox::StandardButton::Cancel);
    mb.setDefaultButton(QMessageBox::StandardButton::Cancel);
    int ret = mb.exec();
    if(ret == QMessageBox::StandardButton::Yes){
        for(QGraphicsItem* item : scene->selectedItems()){
            if(auto obj = dynamic_cast<MultiCanvasObject*>(item)){
            remItemByCanvasObject(obj);
            }
        }
    }
}

void RoomCanvas::keyPressEvent(QKeyEvent *event){
    Qt::Key key = static_cast<Qt::Key>(event->key());
    emit keyPressed(event->key());
    pressedKeys.push_back(key);
    if(pressedKeys.size()>=3){
        pressedKeys.pop_front();
    }
    if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_Delete)){
        ui->actionRemove_Selected->trigger();
        pressedKeys.clear();
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_M)){
        ui->actionMove_Selected->trigger();
        pressedKeys.clear();
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_P)){
        if(canvas->hasMouseTracking()){
            canvas->setMouseTracking(false);
        }else{
            canvas->setMouseTracking(true);
        }
        pressedKeys.clear();
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_A)){
        for(QGraphicsItem* item : scene->selectedItems()){
            QPointF pos = item->pos();
            pos.setX(pos.x()-1);
            item->setPos(pos);
        }
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_D)){
        for(QGraphicsItem* item : scene->selectedItems()){
            QPointF pos = item->pos();
            pos.setX(pos.x()+1);
            item->setPos(pos);
        }
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_W)){
        for(QGraphicsItem* item : scene->selectedItems()){
            QPointF pos = item->pos();
            pos.setY(pos.y()-1);
            item->setPos(pos);
        }
    }
    else if(pressedKeys.contains(Qt::Key_Control) && pressedKeys.contains(Qt::Key_S)){
        for(QGraphicsItem* item : scene->selectedItems()){
            QPointF pos = item->pos();
            pos.setY(pos.y()+1);
            item->setPos(pos);
        }
    }
    return QWidget::keyPressEvent(event);
}

void RoomCanvas::keyReleaseEvent(QKeyEvent *event){
    Qt::Key key = static_cast<Qt::Key>(event->key());
    pressedKeys.removeAll(key);
    return QWidget::keyReleaseEvent(event);
}

void RoomCanvas::on_actionRename_Item_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Rename Item");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    QInputDialog dialog;
    QString name = dialog.getText(this,"Rename Item","What would you like to rename the item to?");
    if(!name.isEmpty()){
        for(QGraphicsItem* item : selectedItems){
            if(auto obj = dynamic_cast<MultiCanvasObject*>(item)){
                obj->setName(name);
            }
        }
        updateLayers();
    }
}

void RoomCanvas::on_actionAdd_child_sprite_file_to_selected_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Add child sprite to selected");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(selectedItems.size() > 1){
        QMessageBox mb(this);
        mb.setWindowTitle("Add child sprite to selected");
        mb.setText("You have selected more than one layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    QString dir = getFilePath();
    MultiCanvasObject* parent = (MultiCanvasObject*)selectedItems.at(0);
    MultiCanvasObject* child = new MultiCanvasObject(parent);
    child->setID(parent->child_id_increment);
    parent->child_id_increment++;
    updateLayers();
}


void RoomCanvas::on_actionScale_Selected_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Add child sprite to selected");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(selectedItems.size() > 1){
        QMessageBox mb(this);
        mb.setWindowTitle("Add child sprite to selected");
        mb.setText("You have selected more than one layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    for(QGraphicsItem* item : selectedItems){
        MultiCanvasObject* obj = (MultiCanvasObject*) item;
        item->setScale(0.5);
    }
}

/*void RoomCanvas::setDialogFilePaths(PropertiesDialog& dialog, MultiCanvasObject* obj, STATE state){
    dialog.clearFilePaths();
    for(PROPERTIES* properties : obj->getFrames().keys()){
        if(properties->state == state){
            if(properties->direction == DIRECTION::SW){
                dialog.setSWLoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::S){
                dialog.setSLoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::SE){
                dialog.setSELoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::E){
                dialog.setELoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::NE){
                dialog.setNELoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::N){
                dialog.setNLoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::NW){
                dialog.setNWLoc(properties->filePath);
                dialog.updateFilePaths();
            }else if(properties->direction == DIRECTION::W){
                dialog.setWLoc(properties->filePath);
                dialog.updateFilePaths();
            }
        }
    }
}*/

/*void RoomCanvas::on_actionObject_Properties_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Object Properties");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(selectedItems.size() > 1){
        QMessageBox mb(this);
        mb.setWindowTitle("Object Properties");
        mb.setText("You have selected more than one layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    PropertiesDialog dialog(this);
    MultiCanvasObject* obj = (MultiCanvasObject*)selectedItems.at(0);
    setDialogFilePaths(dialog,obj,obj->getCurrentState());
    connect(&dialog,&PropertiesDialog::stateChanged,[&](){
        qDebug() << "Changed state to " << dialog.getState();
        if(dialog.getState()=="Standing"){
            setDialogFilePaths(dialog,obj,STATE::STANDING);
        }else if(dialog.getState()=="Walking"){
            setDialogFilePaths(dialog,obj,STATE::WALKING);
        }else if(dialog.getState()=="Sitting"){
            setDialogFilePaths(dialog,obj,STATE::SITTING);
        }else if(dialog.getState()=="Dancing"){
            setDialogFilePaths(dialog,obj,STATE::DANCING);
        }else if(dialog.getState()=="Waving"){
            setDialogFilePaths(dialog,obj,STATE::WAVING);
        }
    });
    int ret = dialog.exec();
    qDebug() << ret;
    if(ret == 1){
        QString state = dialog.getState();
        QString sLoc = dialog.getSLoc();
        QString seLoc = dialog.getSELoc();
        QString eLoc = dialog.getELoc();
        QString neLoc = dialog.getNELoc();
        QString nLoc = dialog.getNLoc();
        QString nwLoc = dialog.getNWLoc();
        QString wLoc = dialog.getWLoc();
        QString swLoc = dialog.getSWLoc();
        if(!sLoc.isEmpty()){
            obj->initFrames(sLoc,DIRECTION::S,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!seLoc.isEmpty()){
            obj->initFrames(seLoc,DIRECTION::SE,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!eLoc.isEmpty()){
            obj->initFrames(eLoc,DIRECTION::E,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!neLoc.isEmpty()){
            obj->initFrames(neLoc,DIRECTION::NE,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!nLoc.isEmpty()){
            obj->initFrames(nLoc,DIRECTION::N,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!nwLoc.isEmpty()){
            obj->initFrames(nwLoc,DIRECTION::NW,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!wLoc.isEmpty()){
            obj->initFrames(wLoc,DIRECTION::W,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
        if(!swLoc.isEmpty()){
            obj->initFrames(swLoc,DIRECTION::SW,getStateFromString(state));
            obj->setCurrentFrames();
            obj->setFrame(0);
        }
    }
}*/

void RoomCanvas::on_actionSet_origin_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Set Origin");
        mb.setText("You have not selected any layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(selectedItems.size() > 1){
        QMessageBox mb(this);
        mb.setWindowTitle("Set Origin");
        mb.setText("You have selected more than one layer!");
        mb.addButton(QMessageBox::Ok);
        mb.setDefaultButton(QMessageBox::Ok);
        mb.exec();
        return;
    }
    setCursor(Qt::PointingHandCursor);
    selectingOrigin = selectedItems.at(0);
    canvas->setDisabled(true);
}

