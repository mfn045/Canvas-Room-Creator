#include "serverbutton.h"

LoginScreen::Buttons::ServerButton::ServerButton(MultiCanvasObject* parent) : AbstractButton(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.screens.loginscreen.buttons.serverbutton.up"));
    setOver(am->getAssetPath("interface.screens.loginscreen.buttons.serverbutton.over"));
    setDown(am->getAssetPath("interface.screens.loginscreen.buttons.serverbutton.down"));

    setIsClickable(true);
    setIsHoverable(true);

    int r = 0;
    int c = 0;

    GridContainer* container = new GridContainer(this);
    container->color = QColor(255,0,0,255);

    MultiCanvasObject* friend_icon = new MultiCanvasObject();
    PROPERTIES* friend_icon_properties = new PROPERTIES();
    friend_icon_properties->filePath = am->getAssetPath("interface.icons.friend.friend_enabled");
    friend_icon->initFrames(friend_icon_properties->filePath, friend_icon_properties);
    friend_icon->setCurrentFrames(friend_icon_properties);
    friend_icon->setFrame(0);
    friend_icon->setScale(1.1);
    GRIDCONTAINER::CELL_PROPERTIES* cell1 = container->addGridItem(friend_icon,r,c++);
    cell1->verticalAlignment = GRIDCONTAINER::VerticalAlignment::CENTER;

    TextLabel* label = new TextLabel();
    QFont font = label->font();
    font.setFamily("Arial");
    font.setPointSize(10);
    label->getInput()->setFont(font);
    label->setText(R"(<font color="white">Blizzard</font>)");
    GRIDCONTAINER::CELL_PROPERTIES* cell2 = container->addGridItem(label,r,c++);
    cell2->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;
    cell2->verticalAlignment = GRIDCONTAINER::VerticalAlignment::CENTER;
    container->setMaxWidth(c-1,90);

    MultiCanvasObject* safechat_icon = new MultiCanvasObject();
    PROPERTIES* safechat_icon_properties = new PROPERTIES();
    safechat_icon_properties->filePath = am->getAssetPath("interface.icons.safechat");
    safechat_icon->initFrames(safechat_icon_properties->filePath, safechat_icon_properties);
    safechat_icon->setCurrentFrames(safechat_icon_properties);
    safechat_icon->setFrame(0);
    GRIDCONTAINER::CELL_PROPERTIES* cell3 = container->addGridItem(safechat_icon,r,c++);
    cell3->verticalAlignment = GRIDCONTAINER::VerticalAlignment::CENTER;

    for(int i = 0; i < 5; i++){
        MultiCanvasObject* serverplayeractivity_icon = new MultiCanvasObject();
        PROPERTIES* serverplayeractivity_icon_properties = new PROPERTIES();
        serverplayeractivity_icon_properties->filePath = am->getAssetPath("interface.icons.serverplayeractivity.inactive_unit");
        serverplayeractivity_icon->initFrames(serverplayeractivity_icon_properties->filePath, serverplayeractivity_icon_properties);
        serverplayeractivity_icon->setCurrentFrames(serverplayeractivity_icon_properties);
        serverplayeractivity_icon->setFrame(0);
        GRIDCONTAINER::CELL_PROPERTIES* cell4 = container->addGridItem(serverplayeractivity_icon,r,c++);
        cell4->verticalAlignment = GRIDCONTAINER::VerticalAlignment::CENTER;
    }
    container->setHorizontalSpacing(5);
    container->setLeftMargin(5);

    container->updateLayout();

    container->addCallbackFunction([container,this](){
        if(container){
            container->setScale(1.2);
            float x = container->pos().x();
            float centerY = (boundingRect().height()-container->getHeight())/2;
            container->setPos(QPointF(x,centerY));
        }
    });
}
