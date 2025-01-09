#include "chathistory_message.h"

ChatHistory_Message::ChatHistory_Message(CanvasObject* parent) : CanvasObject() {
    if(parent != nullptr){
        setParentItem(parent);
    }

    properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chathistory/chathistory_highlight.svg";
    initFrames(properties->filePath, properties);
    setCurrentFrames(properties);
    setFrame(0);
    setScale(-1);


    setIsClickable(true);
    setIsHoverable(true);
    connect(this,&CanvasObject::hoverEnter,this,&ChatHistory_Message::hoverEnterReceiver);
    connect(this,&CanvasObject::hoverLeave,this,&ChatHistory_Message::hoverLeaveReceiver);

    textLabel = new TextLabel(this);
    textLabel->getInput()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textLabel->getInput()->setMaximumSize(QSize(boundingRect().width(),boundingRect().height()));
    textLabel->getInput()->setMinimumSize(QSize(boundingRect().width(),boundingRect().height()));
    textLabel->getInput()->setStyleSheet("background-color:transparent; border: none; margin: 0; padding: 0; padding-left: 5; color:black;");
    QFont font(textLabel->font());
    font.setFamily("Burbank Small");
    textLabel->setFont(font);
    textLabel->setText("");
    textLabel->getInput()->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}

TextLabel* ChatHistory_Message::getLabel(){
    return this->textLabel;
}

void ChatHistory_Message::setHighlight(){
    setCurrentFrames(properties);
    setFrame(0);
}
void ChatHistory_Message::remHighlight(){
    setCurrentFrames(emptyProperties);
    setFrame(0);
}

void ChatHistory_Message::hoverEnterReceiver(QPointF pos){
    if(!getLabel()->getCurrentText().isEmpty()){
        setHighlight();
    }
    return;
}

void ChatHistory_Message::hoverLeaveReceiver(QPointF pos){
    if(!getLabel()->getCurrentText().isEmpty()){
        remHighlight();
    }
    return;
}
