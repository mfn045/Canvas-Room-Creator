#include "categorybutton.h"

CategoryButton::CategoryButton(MultiCanvasObject* parent) : MultiCanvasObject(parent) {
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/inventory/categorybutton/1.svg";

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
