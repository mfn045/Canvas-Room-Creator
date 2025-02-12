#include "whitesquarebutton.h"

WhiteSquareButton::WhiteSquareButton(MultiCanvasObject* parent, SIZE size) : AbstractButton(parent)
{
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    if(size == SIZE::SMALL){
        setUp(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.small.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.small.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.small.over"));
        setDisabled(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.small.disabled"));
    }else if(size == SIZE::MEDIUM){
        setUp(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.medium.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.medium.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.medium.over"));
        setDisabled(am->getAssetPath("interface.widgets.buttons.whitesquarebutton.medium.disabled"));
    }
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
