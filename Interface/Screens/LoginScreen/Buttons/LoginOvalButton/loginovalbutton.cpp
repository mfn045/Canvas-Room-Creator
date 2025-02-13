#include "loginovalbutton.h"

LoginOvalButton::LoginOvalButton(MultiCanvasObject* parent, SIZE size) : AbstractButton(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    if(size == SMALL){
        setUp(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.small.up"));
        setDown(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.small.down"));
        setOver(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.small.over"));
    } else if(size == MEDIUM){
        setUp(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.medium.up"));
        setDown(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.medium.down"));
        setOver(am->getAssetPath("interface.screens.loginscreen.buttons.ovalbutton.medium.over"));
    }
    setIsClickable(true);
    setIsHoverable(true);
}

void LoginOvalButton::setText(QString text){
    if(label == nullptr){
        label = new TextLabel(this);
    }
    qDebug() << text;
    QTransform inversedParent = transform().inverted();
    label->setTransform(inversedParent);
    label->setMaximumHeight(boundingRect().height());
    label->setMaximumWidth(boundingRect().width());
    label->setMinimumHeight(boundingRect().height());
    label->setMinimumWidth(boundingRect().width());

    label->getInput()->setAlignment(Qt::AlignCenter);
    QFont font = label->getInput()->font();
    font.setFamily("Arial Narrow");
    font.setPointSize(12);
    label->getInput()->setStyleSheet("background: transparent;color:white;");
    label->getInput()->setFont(font);
    label->getInput()->setText(text);
    QRectF rect = inversedParent.map(label->boundingRect()).boundingRect();
    float centerX = (boundingRect().width()-rect.width())/2;
    float centerY = (boundingRect().height()-rect.height())/2;
    label->setPos(QPointF(centerX,centerY));
}
