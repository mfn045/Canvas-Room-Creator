#include "playercard.h"

PlayerCard::PlayerCard(Scene* scene) {
    if(scene != nullptr){
        this->scene = scene;
    }
    hide();
    AssetsManager* am = AssetsManager::getInstance();
    setIcon(am->getAssetPath("interface.icons.rectbuttonstripes"));
    setPos(QPointF(100,100));
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setIsClickable(true);
    setIsHoverable(true);

    body = new BackgroundContainer();
    body->setWidth(233);
    body->setHeight(305);
    body->init();
    body->setParentItem(this);
    body->setZValue(1);
    body->setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    float centerX = (boundingRect().width()-body->getWidth())/2;
    body->setPos(QPointF(centerX,this->boundingRect().height()-6));

    container = new GridContainer(body);
    container->setVerticalAlignment(GRIDCONTAINER::VerticalAlignment::TOP);
    container->setHorizontalAlignment(GRIDCONTAINER::HorizontalAlignment::CENTER);
    container->setTopMargin(10);
    container->setVerticalSpacing(5);

    badge = new Badge(container,PENGUIN::BADGE::NONE);
    badge->setZValue(1);
    GRIDCONTAINER::CELL_PROPERTIES* badge_CP = container->addGridItem(badge,0,0);
    badge_CP->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::LEFT;

    username = new TextLabel();
    QFont font = username->getInput()->font();
    font.setFamily("Burbank Small Medium");
    font.setPointSize(11);
    font.setBold(true);
    username->getInput()->setFont(font);
    username->setTextLimit(13);
    username->setText("");
    username->setMaximumWidth(110);
    username->setMaximumHeight(container->getMaxHeight(0));
    container->addGridItem(username,0,1);

    CircleButton* xButton = new CircleButton();
    xButton->setIcon(am->getAssetPath("interface.icons.close"));
    GRIDCONTAINER::CELL_PROPERTIES* xButton_CP = container->addGridItem(xButton,0,2);
    xButton_CP->horizontalAlignment = GRIDCONTAINER::HorizontalAlignment::RIGHT;
    connect(xButton,&CircleButton::clicked,[this](){
        hide();
    });

    bg = new MultiCanvasObject();
    PROPERTIES* bg_properties = new PROPERTIES();
    bg_properties->filePath = am->getAssetPath("interface.widgets.playercard.penguinpaper_background");
    bg->initFrames(bg_properties->filePath,bg_properties);
    bg->setCurrentFrames(bg_properties);
    bg->setFrame(0);
    bg->setZValue(0);
    container->addGridItem(bg,1,0,3,1);

    //417 403 443 413 474
    //penguin_paper->setFace(133);
    //penguin_paper->setHead(417);


    GridContainer* buttonsContainer = new GridContainer(container);
    buttonsContainer->setTopMargin(5);
    buttonsContainer->setHorizontalSpacing(5);

    CircleButton* friendButton = new CircleButton();
    friendButton->setIcon(am->getAssetPath("interface.icons.friend.friend_enabled"));
    buttonsContainer->addGridItem(friendButton,0,0);

    CircleButton* findButton = new CircleButton();
    findButton->setIcon(am->getAssetPath("interface.icons.help.help_enabled"));
    buttonsContainer->addGridItem(findButton,0,1);

    CircleButton* iglooButton = new CircleButton();
    iglooButton->setIcon(am->getAssetPath("interface.icons.igloo.igloo_enabled"));
    buttonsContainer->addGridItem(iglooButton,0,2);

    CircleButton* mailButton = new CircleButton();
    mailButton->setIcon(am->getAssetPath("interface.icons.mail.mail_enabled"));
    buttonsContainer->addGridItem(mailButton,0,3);

    CircleButton* stampButton = new CircleButton();
    stampButton->setIcon(am->getAssetPath("interface.icons.stamp.stamp_enabled"));
    buttonsContainer->addGridItem(stampButton,0,4);

    CircleButton* ignoreButton = new CircleButton();
    ignoreButton->setIcon(am->getAssetPath("interface.icons.ignore.ignore_enabled"));
    buttonsContainer->addGridItem(ignoreButton,0,5);

    CircleButton* reportButton = new CircleButton();
    reportButton->setIcon(am->getAssetPath("interface.icons.moderator.moderator_enabled"));
    buttonsContainer->addGridItem(reportButton,0,6);
    buttonsContainer->updateLayout();

    container->addGridItem(buttonsContainer,2,0,3);

    container->setMaxWidth(0,badge->sceneBoundingRect().width());
    container->setMaxWidth(1,206-badge->sceneBoundingRect().width()-25);
    container->setMaxWidth(2,25);
    container->setMaxHeight(0,25);

    container->updateLayout();

    /*float bg_centerX = (body->getWidth()-container->getWidth())/2;
    float bg_centerY = (body->getHeight()-container->getHeight())/2;
    qDebug() << container->pos();
    qDebug() << "BG CENTER X: " << body->getWidth() << container->getWidth() << bg_centerX;
    qDebug() << "BG CENTER Y: " << body->getHeight() << container->getHeight() << bg_centerY;
    container->setPos(QPointF(bg_centerX,bg_centerY));
    qDebug() << container->pos();*/


    inventory = new Inventory(this);
}

/* CENTER PAPER
    float pp_centerX = (bg->boundingRect().width()-penguin_paper->boundingRect().width())/2;
    float pp_centerY = (bg->boundingRect().height()-penguin_paper->boundingRect().height())-10;
    penguin_paper->setPos(QPointF(pp_centerX, pp_centerY));
*/

MultiCanvasObject* PlayerCard::getBackground(){
    return this->bg;
}


Player* PlayerCard::setPlayer(Player* player){
    this->player = player;

    badge->setBadge(player->getBadge());

    QFont font = username->getInput()->font();
    font.setFamily("Burbank Small Medium");
    font.setPointSize(11);
    font.setBold(true);
    username->getInput()->setFont(font);
    username->setTextLimit(13);
    username->setText(player->getUsername());
    username->setMaximumWidth(110);
    username->setMaximumHeight(container->getMaxHeight(0));

    PenguinPaper* paper = this->player->getPenguinPaper();

    paper->setParentItem(bg);
    float pp_centerX = (bg->boundingRect().width()-paper->boundingRect().width())/2;
    float pp_centerY = (bg->boundingRect().height()-paper->boundingRect().height())-10;
    paper->setPos(QPointF(pp_centerX, pp_centerY));

    container->setMaxWidth(0,badge->sceneBoundingRect().width());
    container->setMaxWidth(1,206-badge->sceneBoundingRect().width()-25);
    container->setMaxWidth(2,25);
    container->setMaxHeight(0,25);

    container->updateLayout();

    if(inventory != nullptr){
        inventory->setPlayer(player);
    }
    return player;
}

Player* PlayerCard::currentPlayer(){
    return player;
}

Inventory* PlayerCard::getInventory(){
    return inventory;
}
