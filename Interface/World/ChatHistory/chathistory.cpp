#include "chathistory.h"

ChatHistory::ChatHistory(Scene* scene) : BlueRectButton() {
    if(scene != nullptr){
        this->scene = scene;
    }
    AssetsManager* am = AssetsManager::getInstance();
    setFlag(AbstractButton::GraphicsItemFlag::ItemIsMovable);
    setScale(-1);
    setIcon(am->getAssetPath("interface.icons.arrows.up"));
    double centerX = (scene->width()-boundingRect().width())/2;
    double centerY = -5;
    setPos(QPointF(boundingRect().width()+centerX,boundingRect().height()+centerY));

    historyBox = new MultiCanvasObject();
    historyBox->setScale(-1);
    historyBox->setFlag(GraphicsItemFlag::ItemStacksBehindParent);
    historyBox->setParentItem(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.widgets.chathistory.chathistory_background");
    historyBox->initFrames(properties->filePath,properties);
    historyBox->setCurrentFrames(properties);
    historyBox->setFrame(0);

    double chatHistory_centerX = ((historyBox->boundingRect().width()-boundingRect().width())/2)+boundingRect().width();
    QPointF historyPos = historyBox->pos();
    historyPos.setX(chatHistory_centerX);
    historyPos.setY(historyPos.y()+boundingRect().height()-5+historyBox->boundingRect().height());
    historyBox->setPos(historyPos);

    maxHeight = historyBox->boundingRect().height();

    GridContainer* container = new GridContainer(historyBox);
    container->setVerticalSpacing(5);
    container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
    container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);

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
