#include "checkboxbutton.h"

CheckBoxButton::CheckBoxButton(MultiCanvasObject* parent) : AbstractButton(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.widgets.buttons.checkboxbutton.up"));
    setDown(am->getAssetPath("interface.widgets.buttons.checkboxbutton.down"));
    setOver(am->getAssetPath("interface.widgets.buttons.checkboxbutton.over"));
    setDisabled(am->getAssetPath("interface.widgets.buttons.checkboxbutton.disabled"));

    setToggleMode(true);
    setToggleOn(false);

    setIsClickable(true);
    setIsHoverable(true);

    connect(this,&AbstractButton::toggledOn, this, &CheckBoxButton::toggledOn);
    connect(this,&AbstractButton::toggledOff, this, &CheckBoxButton::toggledOff);
}

MultiCanvasObject* CheckBoxButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new MultiCanvasObject();
        icon->setParentItem(this);
    }
    properties->filePath = filePath;
    icon->initFrames(properties->filePath,properties);
    icon->setCurrentFrames(properties);
    icon->setFrame(0);
    icon->setScale(2.073578);
    float centerY = (boundingRect().height()-icon->boundingRect().height())/2;
    icon->setPos(QPointF(4.3,-4.95));
    return icon;
}

void CheckBoxButton::toggledOn(){
    if(icon == nullptr){
        AssetsManager* am = AssetsManager::getInstance();
        setIcon(am->getAssetPath("interface.widgets.buttons.checkboxbutton.check"));
    }else{
        icon->show();
    }
}
void CheckBoxButton::toggledOff(){
    if(icon != nullptr){
        icon->hide();
    }
}
