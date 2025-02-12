#include "mail.h"

Mail::Mail(MultiCanvasObject* parent) : AbstractButton(parent) {
    setIsHoverable(true);
    setIsClickable(true);

    setConstPosition(CONST_POSITION::BOTTOM);

    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.world.buttons.mail.up"));
    setDown(am->getAssetPath("interface.world.buttons.mail.down"));
    setOver(am->getAssetPath("interface.world.buttons.mail.over"));

    notification = new Notification(this);
    notification->setPos(QPointF(25,-5));
    notification->setConstPosition(CONST_POSITION::BOTTOM);
    notification->setNumber(38);
}


void Mail::animationIn(){
    QPointF currentPos = pos();
    qDebug() << "ANIMATION IN!!!!";
    qDebug() << currentPos;
    float initialY = -25;
    const float referenceY = currentPos.y();
    currentPos.setY(initialY);
    setPos(currentPos);
    show();/*
    animationThread = QThread::create([=](){
        QPointF currentPos = pos();
        float sum = 0;
        float t = 0;
        while(true){
            float outputY = currentPos.y();
            if(outputY > referenceY*0.98 && outputY < referenceY*1.02){
                currentPos.setY(referenceY);
                break;
            }
            float dt = 0.005;
            float error = referenceY-outputY;
            float c = (-0.5+1*sum);//*exp(-1*t);
            sum += error;
            qDebug() << currentPos << referenceY << sum << c << outputY;
            currentPos.setY(c);
            setPos(currentPos);
            t+=dt;
            QThread::msleep(dt*1000);
        }
        animationThread->terminate();
    });
    animationThread->start();*/
}


Notification* Mail::getNotification(){
    return this->notification;
}
