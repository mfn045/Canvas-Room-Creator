#include "whiterectbutton.h"

WhiteRectButton::WhiteRectButton(MultiCanvasObject* parent, SIZE size, TYPE type) : AbstractButton(parent)
{
    QString path = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/whiterectbutton/";
    QString sizeStr = "";
    QString typeStr = "";

    if(size == SIZE::SMALL){
        sizeStr = "small/";
    }else if(size == SIZE::MEDIUM){
        sizeStr = "medium/";
    }

    if(type == TYPE::WITHOUT_ARROW){
        typeStr = "without_arrow/";
    }else if(type == TYPE::WITH_ARROW){
        typeStr = "with_arrow/";
    }

    QString upButton = path + sizeStr + typeStr + "up.svg";
    QString overButton = path + sizeStr + typeStr + "over.svg";
    QString downButton = path + sizeStr + typeStr + "down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);
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
