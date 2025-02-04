#include "circlebutton.h"

CircleButton::CircleButton(MultiCanvasObject* parent, COLOR color) : AbstractButton(parent)
{
    QString colorPath = "";
    if(color == COLOR::BLUE){
        colorPath = "bluecirclebutton";
    }else if(color == COLOR::WHITE){
        colorPath = "whitecirclebutton";
    }
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/" + colorPath + "/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/" + colorPath + "/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/" + colorPath + "/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);

    setScale(1.2);
}

MultiCanvasObject* CircleButton::setIcon(QString filePath){
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
