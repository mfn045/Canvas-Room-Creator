#include "toolbar.h"

ToolBar::ToolBar(Scene *parent)
    : parent{(Scene*)parent}
{
    parent->installEventFilter(this);
    setIsClickable(true);
    AssetsManager* am = AssetsManager::getInstance();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.widgets.toolbar.toolbar_background");

    initFrames(properties->filePath,properties);
    setCurrentFrames(properties);
    setFrame(0);

    QRectF rect = boundingRect();
    QRectF sceneRect = parent->sceneRect();
    int placement_x = (sceneRect.width()-rect.width())/2;
    setIsMouseTrackable(false);
    setPos(QPointF(placement_x,sceneRect.bottomLeft().y()-rect.height()));

    GridContainer* container = new GridContainer(this);
    container->setHorizontalSpacing(5);
    container->setVerticalSpacing(5);
    container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
    container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::CENTER);
    container->setTopMargin(12);

    puffleTricks_Button = new CircleButton();
    //QRectF buttonSize = safeChat_Button->boundingRect();
    //safeChat_Button->setPos(QPointF(17,12));
    MultiCanvasObject* obj = puffleTricks_Button->setIcon(am->getAssetPath("interface.icons.close"));
    obj->renderer()->setViewBox(QRectF(0,-40,0.001,50));
    container->addGridItem(puffleTricks_Button,0,0);

    emoticons_Button = new CircleButton();
    //emoticons_Button->setPos(QPointF(17+(buttonSize.width()+5)*1,12));
    emoticons_Button->setIcon(am->getAssetPath("interface.icons.emoticon_tongueOut"));
    container->addGridItem(emoticons_Button,0,1);

    penguinState_Button = new CircleButton();
    //penguinState_Button->setPos(QPointF(17+(buttonSize.width()+5)*2,12));
    penguinState_Button->setIcon(am->getAssetPath("interface.icons.penguinstate"));
    container->addGridItem(penguinState_Button,0,2);

    snowBall_Button = new CircleButton();
    //snowBall_Button->setPos(QPointF(17+(buttonSize.width()+5)*3,12));
    snowBall_Button->setIcon(am->getAssetPath("interface.icons.snowballv2"));
    container->addGridItem(snowBall_Button,0,3);

    chat = new MultiCanvasObject();
    chat->setIsClickable(true);
    PROPERTIES* chatProperties = new PROPERTIES();
    chatProperties->filePath = am->getAssetPath("interface.widgets.toolbar.chatbar_input_background");
    chat->initFrames(chatProperties->filePath, chatProperties);
    chat->setCurrentFrames(chatProperties);
    chat->setFrame(0);
    //chat->setPos(QPointF(17+(buttonSize.width()+5)*4+5,12));
    container->addGridItem(chat,0,4);
    qDebug() << chat->boundingRect() << chat->pos();

    safeChat_Button = new CircleButton(chat);
    //sendChat_Button->setPos(QPointF(17+(buttonSize.width()+5)*13,12));
    safeChat_Button->setIcon(am->getAssetPath("interface.icons.safechat"));
    safeChat_Button->setPos(QPointF(0,0));

    chatInput = new TextBox(chat);
    chatInput->setTextLimit(48);
    chatInput->getInput()->setWordWrapMode(QTextOption::NoWrap);
    //chatInput->setTextWidth(chat->boundingRect().width()-40);
    //chatInput->setTextInteractionFlags(Qt::TextEditorInteraction);
    QFont font = chatInput->font();
    font.setFamily("Burbank Small Medium");
    font.setPointSize(9);
    chatInput->setFont(font);
    chatInput->setPos(QPointF(30,2.5));

    sendChat_Button = new CircleButton(chat);
    //sendChat_Button->setPos(QPointF(17+(buttonSize.width()+5)*13,12));
    sendChat_Button->setIcon(am->getAssetPath("interface.icons.sendchat"));
    QPointF sendChatPos = sendChat_Button->pos();
    QRectF sendChatBoundingRect = (sendChat_Button->boundingRect()*sendChat_Button->sceneTransform()).boundingRect();
    sendChatPos.setX(chat->boundingRect().width()-sendChatBoundingRect.width());
    sendChat_Button->setPos(sendChatPos);

    playerCard_Button = new CircleButton();
    //playerCard_Button->setPos(QPointF(17+(buttonSize.width()+5)*14,12));
    playerCard_Button->setIcon(am->getAssetPath("interface.icons.player.band_123"));
    container->addGridItem(playerCard_Button,0,5);

    friends_Button = new CircleButton();
    //friends_Button->setPos(QPointF(17+(buttonSize.width()+5)*15,12));
    friends_Button->setIcon(am->getAssetPath("interface.icons.friend.friend_enabled"));
    container->addGridItem(friends_Button,0,6);


    igloo_Button = new CircleButton();
    //igloo_Button->setPos(QPointF(17+(buttonSize.width()+5)*16,12));
    igloo_Button->setIcon(am->getAssetPath("interface.icons.igloo.igloo_enabled"));
    container->addGridItem(igloo_Button,0,7);

    settings_Button = new CircleButton();
    //settings_Button->setPos(QPointF(17+(buttonSize.width()+5)*17,12));
    settings_Button->setIcon(am->getAssetPath("interface.icons.settings"));
    container->addGridItem(settings_Button,0,8);


    container->updateLayout();
}


CircleButton* ToolBar::getSendChatButton(){
    return this->sendChat_Button;
}


TextBox* ToolBar::getChatInput(){
    return this->chatInput;
}
