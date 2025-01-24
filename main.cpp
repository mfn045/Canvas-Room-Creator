#include "roomcanvas.h"
#include "Objects/Penguin/penguin.h"
#include "Interface/MenuBar/menubar.h"
#include "Interface/News/news.h"
#include "Interface/Map/map.h"
#include "Interface/Mail/mail.h"
#include "Interface/Friend_Requests/friend_requests.h"
#include "Interface/Dialogs/YesNoDialog/yesnodialog.h"
#include "Interface/Buttons/OrangeButton/orangebutton.h"
#include "Interface/SvgGridContainer/gridcontainer.h"
#include "Interface/Buttons/WhiteSquareButton/whitesquarebutton.h"
#include "Interface/ChatHistory/chathistory.h"
#include "Interface/interface.h"
#include "Interface/PlayerCard/playercard.h"
#include "Objects/Penguin/clothingitem.h"
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

    ClothingItem* item = new ClothingItem();
    CanvasObject::PROPERTIES* properties = new CanvasObject::PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/shapes/frames/1.svg";
    item->initFrames(properties->filePath, properties);
    item->setCurrentFrames(properties);
    item->setFrame(0);
    item->setScale(5);
    //item->updateViewbox();
    w.getScene()->addItem(item);
    item->setPos(QPointF(100,100));

    /*YesNoDialog* dialog = new YesNoDialog(w.getScene(),YesNoDialog::TYPE::ORANGE);
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->insertText("Hello there! Are you enjoying CP?");
    dialog->initDialog();
    w.getScene()->addItem(dialog);*/

    /*CanvasObject* rect = new CanvasObject();
    CanvasObject::PROPERTIES* properties = new CanvasObject::PROPERTIES();
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
    qDebug() << " -------------- END --------------- ";


    return a.exec();
}
