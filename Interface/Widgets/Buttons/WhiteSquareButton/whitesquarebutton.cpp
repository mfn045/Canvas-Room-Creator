#include "whitesquarebutton.h"

WhiteSquareButton::WhiteSquareButton(MultiCanvasObject* parent, SIZE size) : AbstractButton(parent)
{
    QString path = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/whitesquarebutton/";
    QString type = "";

    if(size == SIZE::SMALL){
        type = "small/";
    }else if(size == SIZE::MEDIUM){
        type = "medium/";
    }

    QString upButton = path + type + "up.svg";
    QString overButton = path + type + "over.svg";
    QString downButton = path + type + "down.svg";
    QString disabledButton = path + type + "disabled.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
    setDisabled(disabledButton);
}

MultiCanvasObject* WhiteSquareButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new MultiCanvasObject();
        icon->setParentItem(this);
    }
    properties->filePath = filePath;
    icon->initFrames(properties->filePath,properties);
    icon->setCurrentFrames(properties);
    icon->setFrame(0);
    int centerX = (boundingRect().width()-icon->boundingRect().width())/2;
    int centerY = (boundingRect().height()-icon->boundingRect().height())/2;
    icon->setPos(QPointF(centerX,centerY-1));
    return icon;
}
