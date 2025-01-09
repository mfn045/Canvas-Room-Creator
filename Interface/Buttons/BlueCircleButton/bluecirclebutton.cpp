#include "bluecirclebutton.h"

BlueCircleButton::BlueCircleButton(CanvasObject* parent) : AbstractButton(parent)
{
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluecirclebutton/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluecirclebutton/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/bluecirclebutton/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);

    setScale(1.2);
}

void BlueCircleButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new CanvasObject();
        icon->setParentItem(this);
    }
    properties->filePath = filePath;
    icon->initFrames(properties->filePath,properties);
    icon->setCurrentFrames(properties);
    icon->setFrame(0);
    int centerX = (boundingRect().width()-icon->boundingRect().width())/2;
    int centerY = (boundingRect().height()-icon->boundingRect().height())/2;
    icon->setPos(QPointF(centerX,centerY-1));
}
