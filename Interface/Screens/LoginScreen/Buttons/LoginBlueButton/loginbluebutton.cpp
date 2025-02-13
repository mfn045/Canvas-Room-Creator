#include "loginbluebutton.h"

LoginBlueButton::LoginBlueButton(MultiCanvasObject* parent) : AbstractButton(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.screens.loginscreen.buttons.bluebutton.up"));
    setDown(am->getAssetPath("interface.screens.loginscreen.buttons.bluebutton.down"));
    setOver(am->getAssetPath("interface.screens.loginscreen.buttons.bluebutton.over"));

    setIsClickable(true);
    setIsHoverable(true);
}

void LoginBlueButton::setText(QString text){
    if(label == nullptr){
        label = new TextLabel(this);
    }

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
