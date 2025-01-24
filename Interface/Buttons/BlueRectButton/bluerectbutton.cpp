#include "bluerectbutton.h"

BlueRectButton::BlueRectButton(CanvasObject* parent) : AbstractButton(parent)
{
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluerectbutton/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluerectbutton/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluerectbutton/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
}

CanvasObject* BlueRectButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new CanvasObject();
        icon->setParentItem(this);
    }
    properties->filePath = filePath;
    icon->initFrames(properties->filePath,properties);
    icon->setCurrentFrames(properties);
    icon->setFrame(0);
    QRectF iconRect = icon->mapRectToParent(icon->boundingRect());
    double centerX = (boundingRect().width()-iconRect.width())/2;
    double centerY = (boundingRect().height()-iconRect.height())/2;
    icon->setPos(QPointF(centerX,centerY+4));
    return icon;
}
