#include "chatbubble.h"

ChatBubble::ChatBubble(CanvasObject* parent, QString msg) {
    setParentItem(parent);
    this->bubbleMsg = msg;
    QString chatbubble = "";
    double offsetY = 0;
    int fontSize = 6;
    double fontHeight = fontSize+3;
    if(msg.size() < 12){
        offsetY = fontHeight*2.5;
        bubbleType = TYPE::SMALL;
        chatbubble = chatbubble_small;
    }else if(msg.size() < 24){
        offsetY = fontHeight;
        bubbleType = TYPE::MEDIUM;
        chatbubble = chatbubble_medium;
    }else{
        offsetY = 0;
        bubbleType = TYPE::LARGE;
        chatbubble = chatbubble_large;
    }

    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = chatbubble;
    initFrames(chatbubble,properties);
    setCurrentFrames(properties);
    setFrame(0);
    setScale(6.5);

    bubbleTextLabel = new TextLabel(this);
    bubbleTextLabel->setTextLimit(48);
    //bubbleTextBox->getInput()->setWordWrapMode(QTextOption::WordWrap);

    QFont font(bubbleTextLabel->font());
    font.setFamily("_sans");
    font.setPointSize(fontSize);
    bubbleTextLabel->setFont(font);

    bubbleTextLabel->getInput()->setText(msg);

    bubbleTextLabel->getInput()->setAlignment(Qt::AlignCenter);
    bubbleTextLabel->getInput()->setMaximumWidth(boundingRect().width()-5);
    bubbleTextLabel->getInput()->setMinimumWidth(boundingRect().width()-5);
    bubbleTextLabel->getInput()->setMaximumHeight(boundingRect().height());
    bubbleTextLabel->getInput()->setDisabled(true);

    QPointF textPos = bubbleTextLabel->pos();
    textPos.setY(textPos.y()+offsetY);
    textPos.setX(textPos.x()+(boundingRect().width()-bubbleTextLabel->boundingRect().width())/2);
    bubbleTextLabel->setPos(textPos);

    QRectF parentRect = parent->boundingRect();
    int normalized_x = parent->boundingRect().x()+(boundingRect().width()/2);
    int normalized_y = parent->boundingRect().y()-(boundingRect().height()*4);

    setPos(QPointF(normalized_x,normalized_y));

    timer.setInterval(5000);
    timer.setSingleShot(true);
    timer.callOnTimeout([this](){
        hide();
    });
    timer.start();
}

void ChatBubble::setText(QString msg){
    this->bubbleMsg = msg;
    QString chatbubble = "";
    double offsetY = 0;
    int fontSize = 6;
    double fontHeight = fontSize+3;
    if(msg.size() < 12){
        offsetY = fontHeight*2.5;
        bubbleType = TYPE::SMALL;
        chatbubble = chatbubble_small;
    }else if(msg.size() < 24){
        offsetY = fontHeight;
        bubbleType = TYPE::MEDIUM;
        chatbubble = chatbubble_medium;
    }else{
        offsetY = 0;
        bubbleType = TYPE::LARGE;
        chatbubble = chatbubble_large;
    }
    QFont font(bubbleTextLabel->font());
    font.setFamily("sans");
    font.setPointSize(fontSize);
    bubbleTextLabel->setFont(font);

    bubbleTextLabel->getInput()->setText(msg);

    bubbleTextLabel->getInput()->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    bubbleTextLabel->getInput()->setWordWrap(true);
    bubbleTextLabel->getInput()->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    bubbleTextLabel->getInput()->setMaximumWidth(boundingRect().width()-5);
    bubbleTextLabel->getInput()->setMinimumWidth(boundingRect().width()-5);
    bubbleTextLabel->getInput()->setMaximumHeight(boundingRect().height());
    show();
    timer.setInterval(5000);
    timer.setSingleShot(true);
    timer.callOnTimeout([this](){
        hide();
    });
    timer.start();

}
