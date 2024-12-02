#include "roomcanvas.h"
#include "./ui_roomcanvas.h"

RoomCanvas::RoomCanvas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RoomCanvas)
{
    ui->setupUi(this);

    ui->canvas->setAcceptDrops(true);
    ui->canvas->setRenderHint(QPainter::LosslessImageRendering);
    ui->canvas->setRenderHint(QPainter::Antialiasing);
    ui->canvas->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->canvas->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed));
    ui->canvas->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->canvas,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(QPoint)));

    layers=new Layers();
    layers->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(layers,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(QPoint)));
    ui->layerArea->addWidget(layers);

    connect(layers,SIGNAL(dropped()),this,SLOT(updateItems()));
    connect(layers,SIGNAL(itemSelectionChanged()),this,SLOT(changeGraphicsSelection()));

    scene = new QGraphicsScene();
    QRectF f;
    f.setRect(0,0,800,600);
    scene->setSceneRect(f);
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(changeLayersSelection()));

    ui->canvas->setScene(scene);

    thread = QThread::create([this](){
        while(true){
            QMetaObject::invokeMethod(this,"nextFrame", Qt::QueuedConnection);
            QThread::msleep(30);
        }
    });
    thread->start();
}

RoomCanvas::~RoomCanvas()
{
    delete ui;
}

void RoomCanvas::contextMenuRequested(QPoint point){
    QMenu* menu = new QMenu(this);
    menu->addAction(ui->actionMove_Selected);
    menu->addAction(ui->actionRemove_Selected);

    menu->popup(ui->centralwidget->mapToGlobal(point));
}

void RoomCanvas::changeLayersSelection(){
    if(items.isEmpty() || updatingSelection) return;
    updatingSelection = true;
    layers->clearSelection();
    for(CanvasObject* obj : items){
        if(obj->isSelected()){
            for(int i = 0; i < layers->invisibleRootItem()->childCount(); i++){
                QTreeWidgetItem* selectedTreeItem = layers->invisibleRootItem()->child(i);
                QString layerID = selectedTreeItem->text(1);
                if(layerID.replace("Layer ", "").toInt() == obj->getID()){
                    selectedTreeItem->setSelected(true);
                }
            }
        }
    }
    updatingSelection = false;
}

void RoomCanvas::changeGraphicsSelection(){
    if(items.isEmpty() || updatingSelection) return;
    updatingSelection = true;
    scene->clearSelection();
    for(CanvasObject* obj : items){
        for(QTreeWidgetItem* selectedTreeItem : layers->selectedItems()){
            QString layerID = selectedTreeItem->text(1);
            if(layerID.replace("Layer ", "").toInt() == obj->getID()){
                obj->setSelected(true);
            }
        }
    }
    updatingSelection = false;
}

void RoomCanvas::nextFrame(){
    if(attemptingUpdate) return;
    for(CanvasObject* obj : items){
        if(obj->getFrames().size() >= 2){
            obj->nextFrame();
        }
    }
}

void RoomCanvas::updateLayers(){
    layers->clear();
    for(CanvasObject* obj : items){
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setIcon(0,QIcon(obj->getFrames().at(0)));
        item->setText(1,"Layer " + QString::number(obj->getID()));
        item->setFlags(item->flags() ^ Qt::ItemIsDropEnabled);
        layers->insertTopLevelItem(0,item);
    }
}

void RoomCanvas::updateItems(){
    if(layers->invisibleRootItem() == nullptr) return;
    attemptingUpdate = true;
    qDebug() << "called";
    qDebug() << items;
    QList<CanvasObject*> updatedItems;
    bool updated = false;
    for(int i = 0; i < layers->invisibleRootItem()->childCount(); i++){
        QTreeWidgetItem* item = layers->invisibleRootItem()->child(i);
        QString layerID = item->text(1);
        for(CanvasObject* obj : items){
            if(layerID.replace("Layer ","").toInt() == obj->getID()){
                qDebug() << "updated " << i;
                updatedItems.append(obj);
                updated = true;
            }
        }
    }
    if(updated){
        items = updatedItems;
    }
    qDebug() << items;
    for(QGraphicsItem* item : scene->items()){
        qDebug() << "Item removed " << ((CanvasObject*)item)->getID();
        scene->removeItem(item);
    }
    scene->update();
    for(CanvasObject* obj : items){
        qDebug() << "Item added " << obj->getID();
        scene->addItem(obj);
    }
    scene->update();
    attemptingUpdate = false;
}

QList<CanvasObject*> RoomCanvas::getItems(){
    return this->items;
}

void RoomCanvas::addItem(QString dir){
    if(dir.isEmpty()) return;
    CanvasObject* item = new CanvasObject(dir);
    item->setCursor(Qt::PointingHandCursor);
    items.append(item);
    item->setID(items.size());
    scene->addItem(item);
    updateLayers();
}

void RoomCanvas::remItem(QString dir){
    if(layers->invisibleRootItem() == nullptr) return;
    QList<CanvasObject*> updatedItems;
    for(CanvasObject* obj : items){
        if(obj->getFilePath() != dir){
            updatedItems.append(obj);
        }
    }
    items = updatedItems;
    for(QGraphicsItem* item : scene->items()){
        if(!updatedItems.contains(item)){
            scene->removeItem(item);
        }
    }
    scene->update();
    updateLayers();
}

void RoomCanvas::remItemByID(int id){
    if(layers->invisibleRootItem() == nullptr) return;
    QList<CanvasObject*> updatedItems;
    for(CanvasObject* obj : items){
        if(obj->getID() != id){
            updatedItems.append(obj);
        }
    }
    items = updatedItems;
    for(QGraphicsItem* item : scene->items()){
        if(!updatedItems.contains(item)){
            scene->removeItem(item);
        }
    }
    scene->update();
    updateLayers();
}

void RoomCanvas::on_importSpriteFile_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this,"Select a sprite directory");

    addItem(dir);
}


void RoomCanvas::on_actionImport_Sprite_triggered()
{
    QUrl dir = QFileDialog::getOpenFileUrl(this,"Selected a sprite file");

    addItem(dir.toString().replace("file:///",""));
}


void RoomCanvas::on_actionMove_Selected_triggered()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if(selectedItems.isEmpty()){
        QMessageBox mb;
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
    ui->canvas->setFixedSize(QSize(width+10,height+10));
    //scene->setSceneRect(f);
}


void RoomCanvas::on_actionRemove_Selected_triggered()
{
    for(QGraphicsItem* item : scene->selectedItems()){
        remItemByID(((CanvasObject*)item)->getID());
    }
}

