#include "penguinpaper.h"

PenguinPaper::PenguinPaper(CanvasObject* parent) : CanvasObject(parent) {
    PROPERTIES* pp_properties = new PROPERTIES();
    pp_properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/playercard/penguin_paper/penguin_paper.svg";
    initFrames(pp_properties->filePath,pp_properties);
    setCurrentFrames(pp_properties);
    setFrame(0);
}

void PenguinPaper::changeColor(QString color){
    QDomDocument doc;
    for(auto it = getFrames().begin(); it != getFrames().end(); it++){
        for(QByteArray* ba : it.value()){
            doc.setContent(*ba);
            QDomElement docElement = doc.documentElement();
            QDomElement docChildElement = docElement.firstChildElement();
            while(!docChildElement.isNull()){
                if(docChildElement.attribute("id") == "penguin"){
                    break;
                }
                docChildElement = docChildElement.nextSiblingElement();
            }
            QDomElement targetElement = docChildElement.firstChildElement();

            while (!targetElement.isNull()) {
                if (targetElement.attribute("id") == "body") {
                    break;
                }
                targetElement = targetElement.nextSiblingElement();
            }
            QDomElement childOfTarget = targetElement.firstChildElement();
            while (!childOfTarget.isNull()) {
                if (childOfTarget.hasAttribute("fill")) {
                    childOfTarget.setAttribute("fill",color);
                }
                childOfTarget = childOfTarget.nextSiblingElement();
            }
            *ba = doc.toByteArray();
        }
    }
    refresh();
}


void PenguinPaper::setHead(int headId){
    bool exists = false;
    if(head == nullptr){
        head = loadItem(headId);
    }else {
        exists = true;
    }
    if(exists){
        delete head;
        head = loadItem(headId);
    }
    head->setIsClickable(true);
    head->setIsHoverable(true);
    head->connect(head,&CanvasObject::mousePress, [this](){
        delete head;
        head = nullptr;
    });
    head->setZValue(6);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    if(!head->getCurrentFrames().isEmpty() && head->getCurrentFrames().at(0) != nullptr){
        doc.setContent(*(head->getCurrentFrames().at(0)));
    }
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    head->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}
void PenguinPaper::setFace(int faceId){
    bool exists = false;
    if(face == nullptr){
        face = loadItem(faceId);
    }else {
        exists = true;
    }
    if(exists){
        delete face;
        face = loadItem(faceId);
    }
    face->setIsClickable(true);
    face->setIsHoverable(true);
    face->connect(face,&CanvasObject::mousePress, [this](){
        delete face;
        face = nullptr;
    });
    face->setZValue(5);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    if(face->getCurrentFrames().at(0) != nullptr){
        doc.setContent(*(face->getCurrentFrames().at(0)));
    }
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    qDebug() << "FACE OFFSETS " << offsetX << offsetY;
    face->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}
void PenguinPaper::setNeck(int neckId){
    bool exists = false;
    if(neck == nullptr){
        neck = loadItem(neckId);
    }else {
        exists = true;
    }
    if(exists){
        delete neck;
        neck = loadItem(neckId);
    }
    neck->setIsClickable(true);
    neck->setIsHoverable(true);
    neck->connect(neck,&CanvasObject::mousePress, [this](){
        delete neck;
        neck = nullptr;
    });
    neck->setZValue(4);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    if(neck->getCurrentFrames().at(0) != nullptr){
        doc.setContent(*(neck->getCurrentFrames().at(0)));
    }
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    neck->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}
void PenguinPaper::setBody(int bodyId){
    bool exists = false;
    if(body == nullptr){
        body = loadItem(bodyId);
    }else {
        exists = true;
    }
    if(exists){
        delete body;
        body = loadItem(bodyId);
    }
    body->setIsClickable(true);
    body->setIsHoverable(true);
    body->connect(body,&CanvasObject::mousePress, [this](){
        delete body;
        body = nullptr;
    });
    body->setZValue(3);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    if(body->getCurrentFrames().at(0) != nullptr){
        doc.setContent(*(body->getCurrentFrames().at(0)));
    }
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    body->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}
void PenguinPaper::setHand(int handId){
    bool exists = false;
    if(hand == nullptr){
        hand = loadItem(handId);
    }else {
        exists = true;
    }
    if(exists){
        delete hand;
        hand = loadItem(handId);
    }
    hand->setIsClickable(true);
    hand->setIsHoverable(true);
    hand->connect(hand,&CanvasObject::mousePress, [this](){
        delete hand;
        hand = nullptr;
    });
    hand->setZValue(8);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    doc.setContent(*(hand->getCurrentFrames().at(0)));
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    hand->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}

void PenguinPaper::setFeet(int feetId){
    bool exists = false;
    if(feet == nullptr){
        feet = loadItem(feetId);
    }else {
        exists = true;
    }
    if(exists){
        delete feet;
        feet = loadItem(feetId);
    }
    feet->setIsClickable(true);
    feet->setIsHoverable(true);
    feet->connect(feet,&CanvasObject::mousePress, [this](){
        delete feet;
        feet = nullptr;
    });
    feet->setZValue(2);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    doc.setContent(*(feet->getCurrentFrames().at(0)));
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    feet->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}

void PenguinPaper::setPin(int pinId){
    bool exists = false;
    if(pin == nullptr){
        pin = loadItem(pinId);
    }else {
        exists = true;
    }
    if(exists){
        delete pin;
        pin = loadItem(pinId);
    }
    pin->setIsClickable(true);
    pin->setIsHoverable(true);
    pin->connect(pin,&CanvasObject::mousePress, [this](){
        delete pin;
        pin = nullptr;
    });
    pin->setZValue(1);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    doc.setContent(*(pin->getCurrentFrames().at(0)));
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    pin->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}

void PenguinPaper::setBackground(int backgroundId){
    bool exists = false;
    if(background == nullptr){
        background = loadItem(backgroundId);
    }else {
        exists = true;
    }
    if(exists){
        delete background;
        background = loadItem(backgroundId);
    }
    background->setIsClickable(true);
    background->setIsHoverable(true);
    background->connect(background,&CanvasObject::mousePress, [this](){
        delete background;
        background = nullptr;
    });
    background->setZValue(0);
    float centerX = (boundingRect().width())/2;
    float centerY = (boundingRect().height())/2;
    float initialOffsetY=-12.5;

    QDomDocument doc;
    doc.setContent(*(background->getCurrentFrames().at(0)));
    QDomElement el = doc.documentElement().firstChildElement();
    QString value = el.attribute("transform");
    QStringList list = value.replace("matrix(","").replace(")","").split(", ");

    float offsetX = 0;
    float offsetY = 0;

    if(list.count() == 6){
        offsetX = -1*list[4].toFloat();
        offsetY = -1*list[5].toFloat();
    }
    background->setPos(QPointF(centerX+offsetX,centerY+offsetY+initialOffsetY));
}

void PenguinPaper::setColor(int colorId){
    if(colorId == 1){
        changeColor("#003366");
    }else if(colorId == 2){
        changeColor("#009900");
    }else if(colorId == 3){
        changeColor("#ff3399");
    }else if(colorId == 4){
        changeColor("#333333");
    }else if(colorId == 5){
        changeColor("#cc0000");
    }else if(colorId == 6){
        changeColor("#ff6600");
    }else if(colorId == 7){
        changeColor("#ffcc00");
    }else if(colorId == 8){
        changeColor("#660099");
    }else if(colorId == 9){
        changeColor("#996600");
    }else if(colorId == 10){
        changeColor("#ff6666");
    }else if(colorId == 11){
        changeColor("#006600");
    }else if(colorId == 12){
        changeColor("#0099cc");
    }else if(colorId == 13){
        changeColor("#8ae302");
    }else if(colorId == 14){
        changeColor("#93a0a4");
    }else if(colorId == 15){
        changeColor("#02a797");
    }else if(colorId == 16){
        changeColor("#f0f0d8");
    }
}

CanvasObject* PenguinPaper::loadItem(int id){
    CanvasObject* item = new CanvasObject(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Clothings/1-499/items/";
    properties->filePath += QString::number(id);
    properties->filePath += "/paper/1.svg";
    item->initFrames(properties->filePath,properties);
    item->setCurrentFrames(properties);
    item->setFrame(0);
    item->setIsClickable(true);
    item->setFlag(QGraphicsSvgItem::GraphicsItemFlag::ItemIsMovable,true);
    return item;
}
