#include "chathistory_message.h"

ChatHistory_Message::ChatHistory_Message(MultiCanvasObject* parent) : MultiCanvasObject() {
    if(parent != nullptr){
        setParentItem(parent);
    }

    properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chathistory/chathistory_highlight.svg";
    initFrames(properties->filePath, properties);
    setCurrentFrames(properties);
    setFrame(0);

    emptyProperties = new PROPERTIES();
    emptyProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chathistory/chathistory_nonhighlight.svg";
    initFrames(emptyProperties->filePath, emptyProperties);


    setIsClickable(true);
    setIsHoverable(true);
    connect(this,&MultiCanvasObject::hoverEnter,this,&ChatHistory_Message::hoverEnterReceiver);
    connect(this,&MultiCanvasObject::hoverLeave,this,&ChatHistory_Message::hoverLeaveReceiver);

    textLabel = new TextLabel(this);
    textLabel->setAcceptHoverEvents(false);
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
