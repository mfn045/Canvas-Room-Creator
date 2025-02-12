#include "categorybutton.h"

CategoryButton::CategoryButton(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.widgets.buttons.inventory.categorybutton");

    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);

    if(!button){
        button = new OvalButton(this);
        button->setText("Category");
        float centerX = (boundingRect().width()-button->boundingRect().width())/2;
        float centerY = (boundingRect().height()-button->boundingRect().height())/2;
        button->setPos(QPointF(centerX,centerY-3));
    }
}

OvalButton* CategoryButton::getButton(){
    return button;
}
