#include "bluerectbutton.h"

BlueRectButton::BlueRectButton(MultiCanvasObject* parent) : AbstractButton(parent)
{
    AssetsManager* am = AssetsManager::getInstance();

    setIsHoverable(true);
    setIsClickable(true);


    setUp(am->getAssetPath("interface.widgets.buttons.bluerectbutton.up"));
    setDown(am->getAssetPath("interface.widgets.buttons.bluerectbutton.down"));
    setOver(am->getAssetPath("interface.widgets.buttons.bluerectbutton.over"));
}

MultiCanvasObject* BlueRectButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new MultiCanvasObject();
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
