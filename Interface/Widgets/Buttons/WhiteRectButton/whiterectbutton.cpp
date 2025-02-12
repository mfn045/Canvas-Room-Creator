#include "whiterectbutton.h"

WhiteRectButton::WhiteRectButton(MultiCanvasObject* parent, SIZE size, TYPE type) : AbstractButton(parent)
{
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    if(size == SIZE::SMALL){
        if(type == TYPE::WITHOUT_ARROW){
            setUp(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.without_arrow.up"));
            setDown(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.without_arrow.down"));
            setOver(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.without_arrow.over"));
        }else if(type == TYPE::WITH_ARROW){
            setUp(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.with_arrow.up"));
            setDown(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.with_arrow.down"));
            setOver(am->getAssetPath("interface.widgets.buttons.whiterectbutton.small.with_arrow.over"));
        }
    }else if(size == SIZE::MEDIUM){
        if(type == TYPE::WITHOUT_ARROW){
            setUp(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.without_arrow.up"));
            setDown(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.without_arrow.down"));
            setOver(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.without_arrow.over"));
        }else if(type == TYPE::WITH_ARROW){
            setUp(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.with_arrow.up"));
            setDown(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.with_arrow.down"));
            setOver(am->getAssetPath("interface.widgets.buttons.whiterectbutton.medium.with_arrow.over"));
        }
    }
}

void WhiteRectButton::setText(QString text){
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

MultiCanvasObject* WhiteRectButton::setIcon(QString filePath){
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
