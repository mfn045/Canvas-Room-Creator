#include "ovalbutton.h"

OvalButton::OvalButton(MultiCanvasObject* parent, COLOR color) : AbstractButton(parent)
{
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    if(color == COLOR::WHITE){
        setUp(am->getAssetPath("interface.widgets.buttons.ovalbutton.white.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.ovalbutton.white.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.ovalbutton.white.over"));
    }else if(color == COLOR::BLUE){
        setUp(am->getAssetPath("interface.widgets.buttons.ovalbutton.blue.up"));
        setDown(am->getAssetPath("interface.widgets.buttons.ovalbutton.blue.down"));
        setOver(am->getAssetPath("interface.widgets.buttons.ovalbutton.blue.over"));
    }
}

void OvalButton::setText(QString text){
    if(label == nullptr){
        label = new TextLabel(this);
        label->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
        label->setMinimumSize(boundingRect().size());
        label->setMaximumSize(boundingRect().size());
    }
    QFont font(label->font());
    font.setFamily("Burbank Small Medium");
    font.setPointSize(10);
    label->getInput()->setFont(font);
    label->getInput()->setText(text);
    label->getInput()->setAlignment(Qt::AlignCenter);
}

MultiCanvasObject* OvalButton::setIcon(QString filePath){
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
