#include "roomcanvas.h"
#include "Interface/interface.h"
#include "CanvasObject/Multi/multicanvasobject.h"
#include "CanvasObject/Atlas/atlascanvasobject.h"
#include <QRect>
#include <QFontDatabase>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    RoomCanvas w;
    w.setWindowTitle("Clubpenguin Room Creator");
    w.setWindowIcon(QIcon(":/resources/Resources/logo.png"));
    w.show();

    Interface* interface = Interface::getInstance();
    interface->setScene(w.getScene());
    interface->loadItems();
    interface->loadFonts();
    interface->loadPenguin();
    interface->loadHUD();
    interface->loadPlayerCard();
    interface->getPlayerCard()->getInventory()->setPenguin(interface->getActivePenguin());
/*
    MultiCanvasObject* obj = new MultiCanvasObject();
    MultiCanvasObject::PROPERTIES* properties = new MultiCanvasObject::PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output/test.svg";
    obj->initFrames(properties->filePath,properties);
    obj->setCurrentFrames(properties);
    obj->setFrame(0);
    w.getScene()->addItem(obj);*/


    /*ClothingItem* item = new ClothingItem();
    item->setHasAnimationLoop(true);
    MultiCanvasObject::PROPERTIES* properties = new MultiCanvasObject::PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Clothings/1-499/sprite_export/output/301/26";
    item->initFrames(properties->filePath, properties);
    item->setCurrentFrames(properties);
    item->setFrame(0);
    item->setScale(5);
    //item->updateViewbox();
    w.getScene()->addItem(item);
    item->setPos(QPointF(100,100));*/

    /*YesNoDialog* dialog = new YesNoDialog(w.getScene(),YesNoDialog::TYPE::ORANGE);
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->initDialog();
    w.getScene()->addItem(dialog);*/

    /*CanvasObject* rect = new MultiCanvasObject();
    MultiCanvasObject::PROPERTIES* properties = new MultiCanvasObject::PROPERTIES();
    properties->filePath ="C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/test/test.svg";
    rect->initFrames(properties->filePath,properties);
    rect->setCurrentFrames(properties);
    qDebug() << "RECT UPDATE :: " << rect->boundingRect() << rect->sceneBoundingRect();
    rect->setFrame(0);
    rect->setScale(0.5);
    qDebug() << "RECT UPDATE :: " << rect->boundingRect() << rect->sceneBoundingRect();
    rect->setPos(50,50);
    rect->setID(w.getScene()->getUniqueID());
    w.getScene()->addItem(rect);
    //w.updateLayers();
    w.update();

    GridContainer* container = new GridContainer(rect);
    container->setID(w.getScene()->getUniqueID());
    /*for(int r = 0; r < 2; r++){
        for(int c = 0; c < 2; c++){
            if(r == 2 && c == 2){
                container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::SMALL),r,c);
            }else{
                container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::SMALL),r,c);
            }
        }
    }
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,0);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,1);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,2);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),0,4);
    container->addGridItem(new WhiteSquareButton(nullptr, WhiteSquareButton::SIZE::MEDIUM),2,0);
    container->updateLayout();*/
    qDebug() << " ------------- TEST --------------- ";
    //qDebug() << obj1 << obj1->pos();
    //qDebug() << obj2 << obj2->pos();
    //qDebug() << obj3 << obj3->pos();
    /*AtlasCanvasObject* atlas = new AtlasCanvasObject();
    atlas->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas->setCurrentSprite(10);
    atlas->setFrame(0);
    atlas->setHasAnimationLoop(true);
    w.getScene()->addItem(atlas);*/


    /*AtlasCanvasObject* atlas2 = new AtlasCanvasObject();
    atlas2->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas2->setCurrentSprite(10);
    atlas2->setFrame(0);
    atlas2->setHasAnimationLoop(true);
    atlas2->setPos(QPointF(100,100));
    w.getScene()->addItem(atlas2);


    AtlasCanvasObject* atlas3 = new AtlasCanvasObject();
    atlas3->initFrames("C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/output");
    atlas3->setCurrentSprite(10);
    atlas3->setFrame(0);
    atlas3->setHasAnimationLoop(true);
    atlas3->setPos(QPointF(200,200));
    w.getScene()->addItem(atlas3);
*/
    qDebug() << " -------------- END --------------- ";


    return a.exec();
}
