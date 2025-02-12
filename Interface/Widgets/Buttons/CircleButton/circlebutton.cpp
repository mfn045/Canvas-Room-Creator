#include "circlebutton.h"

CircleButton::CircleButton(MultiCanvasObject* parent, COLOR color) : AbstractButton(parent)
{

    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    if(color == COLOR::BLUE){
        setUp(am->getAssetPath("interface.widgets.buttons.bluecirclebutton.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.bluecirclebutton.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.bluecirclebutton.over"));
    }else if(color == COLOR::WHITE){
        setUp(am->getAssetPath("interface.widgets.buttons.whitecirclebutton.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.whitecirclebutton.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.whitecirclebutton.over"));
    }

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
