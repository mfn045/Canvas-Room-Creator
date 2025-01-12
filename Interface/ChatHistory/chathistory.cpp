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
    historyBox->setScale(-1);
    historyBox->setFlag(GraphicsItemFlag::ItemStacksBehindParent);
    historyBox->setParentItem(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/chathistory/chathistory.svg";
    historyBox->initFrames(properties->filePath,properties);
    historyBox->setCurrentFrames(properties);
    historyBox->setFrame(0);

    double chatHistory_centerX = -(historyBox->boundingRect().width()-boundingRect().width())/2;
    QPointF historyPos = historyBox->pos();
    historyPos.setX(historyPos.x()-chatHistory_centerX);
    historyPos.setY(historyPos.y()+boundingRect().height()-5+historyBox->boundingRect().height());
    historyBox->setPos(historyPos);

    maxHeight = historyBox->boundingRect().height();

    GridContainer* container = new GridContainer(historyBox);
    container->setVerticalSpacing(5);
    container->setHorizontalAlignment(GridContainer::HorizontalAlignment::RIGHT);

    for(int i = 0; i < 15; i++){
        ChatHistory_Message* msg = new ChatHistory_Message(historyBox);
        container->addGridItem(msg,i,0);
        msg->remHighlight();
        pastMessages.push_back(msg);
    }
    container->updateLayout();

    for(int i = 0; i < 30; i++){
        addMessage("Message (" + QString::number(i) + ")");
    }

}
