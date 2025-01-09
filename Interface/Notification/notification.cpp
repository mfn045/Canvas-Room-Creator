#include "notification.h"

Notification::Notification(CanvasObject* parent) : CanvasObject(parent) {
    oneDigitProperties = new PROPERTIES();
    oneDigitProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/notification/onedigit.svg";
    initFrames(oneDigitProperties->filePath,oneDigitProperties);

    twoDigitProperties = new PROPERTIES();
    twoDigitProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/notification/twodigit.svg";
    initFrames(twoDigitProperties->filePath,twoDigitProperties);

    digitLabel = new TextLabel(this);

    setNumber(0);
}


int Notification::setNumber(int number){
    if(number > 99){
        number = 99;
    }else if(number < 0){
        number = 0;
    }
    this->number = number;
    if(this->number == 0){
        hide();
    }else{
        show();
    }
    if(number < 10){
        if(getCurrentProperties() != oneDigitProperties){
            setCurrentFrames(oneDigitProperties);
            setFrame(0);
            QFont font = digitLabel->font();
            font.setFamily("cpBurbankSmallBold");
            font.setBold(true);
            font.setPointSize(10);
            digitLabel->getInput()->setFont(font);
            digitLabel->getInput()->setStyleSheet("background-color:transparent; color:white;");
        }
        digitLabel->setText(QString::number(number));
        digitLabel->getInput()->setAlignment(Qt::AlignCenter);
        double centerX = (boundingRect().width()-digitLabel->getInput()->getWidth())/2;
        double centerY = (boundingRect().height()-digitLabel->getInput()->getHeight())/2;
        digitLabel->setPos(QPointF(centerX,centerY));
    }else if(number >= 10){
        if(getCurrentProperties() != twoDigitProperties){
            setCurrentFrames(twoDigitProperties);
            setFrame(0);
            QFont font = digitLabel->font();
            font.setFamily("cpBurbankSmallBold");
            font.setBold(true);
            font.setPointSize(10);
            digitLabel->getInput()->setFont(font);
            digitLabel->getInput()->setStyleSheet("background-color:transparent; color:white;");
        }
        digitLabel->setText(QString::number(number));
        digitLabel->getInput()->setAlignment(Qt::AlignCenter);
        double centerX = (boundingRect().width()-digitLabel->getInput()->getWidth())/2;
        double centerY = (boundingRect().height()-digitLabel->getInput()->getHeight())/2;
        digitLabel->setPos(QPointF(centerX,centerY));
    }

    return this->number;
}

int Notification::getNumber(){
    return this->number;
}
