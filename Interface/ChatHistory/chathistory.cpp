#include "chathistory.h"

ChatHistory::ChatHistory(Scene* scene) : BlueRectButton() {
    if(scene != nullptr){
        this->scene = scene;
    }
    setFlag(AbstractButton::GraphicsItemFlag::ItemIsMovable);
    setScale(-1);
    setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/arrows/up.svg");
    double centerX = (scene->width()-boundingRect().width())/2;
    double centerY = -5;
    setPos(QPointF(boundingRect().width()+centerX,boundingRect().height()+centerY));

    historyBox = new CanvasObject();
    historyBox->setFlag(GraphicsItemFlag::ItemStacksBehindParent);
    historyBox->setParentItem(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chathistory/chathistory.svg";
    historyBox->initFrames(properties->filePath,properties);
    historyBox->setCurrentFrames(properties);
    historyBox->setFrame(0);

    double chatHistory_centerX = (historyBox->boundingRect().width()-boundingRect().width())/2;
    QPointF historyPos = historyBox->pos();
    historyPos.setX(historyPos.x()-chatHistory_centerX);
    historyPos.setY(historyPos.y()+boundingRect().height()-5);
    historyBox->setPos(historyPos);

    maxHeight = historyBox->boundingRect().height();

    int msgSpacer = 5;
    for(int i = 0; i < 15; i++){
        ChatHistory_Message* msg = new ChatHistory_Message(historyBox);
        int centerX = (historyBox->boundingRect().width()-msg->boundingRect().width())/2;
        msg->setPos(QPointF(historyBox->boundingRect().width()-centerX,historyBox->boundingRect().height()-(2*msgSpacer)-((msg->boundingRect().height()+msgSpacer)*i)));
        msg->remHighlight();
        pastMessages.push_back(msg);
    }

    for(int i = 0; i < 30; i++){
        addMessage("Message (" + QString::number(i) + ")");
    }

}
