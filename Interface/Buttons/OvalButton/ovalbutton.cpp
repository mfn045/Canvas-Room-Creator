#include "ovalbutton.h"

OvalButton::OvalButton(CanvasObject* parent, COLOR color) : AbstractButton(parent)
{
    QString path = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/ovalbutton/";
    QString colorStr = "";

    if(color == COLOR::WHITE){
        colorStr = "white/";
    }else if(color == COLOR::BLUE){
        colorStr = "blue/";
    }

    QString upButton = path + colorStr + "up.svg";
    QString overButton = path + colorStr + "over.svg";
    QString downButton = path + colorStr + "down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
}

void OvalButton::setText(QString text){
    if(label == nullptr){
        label = new TextLabel(this);
        label->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
        label->setMinimumSize(boundingRect().size());
        label->setMaximumSize(boundingRect().size());
    }
    QFont font(label->font());
    font.setFamily("Arial");
    font.setPointSize(10);
    label->getInput()->setFont(font);
    label->getInput()->setText(text);
    label->getInput()->setAlignment(Qt::AlignCenter);
}

CanvasObject* OvalButton::setIcon(QString filePath){
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
    return icon;
}
