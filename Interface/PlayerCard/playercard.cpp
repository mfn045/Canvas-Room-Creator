#include "playercard.h"

PlayerCard::PlayerCard(Scene* scene) {
    if(scene != nullptr){
        this->scene = scene;
    }
    qDebug() << "PLAYER CARD IS BEING SET!!!";
    setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/rectbuttonstripes/rectbuttonstripes.svg");
    setPos(QPointF(100,100));
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setIsClickable(true);
    setIsHoverable(true);

    body = new DialogGrid();
    body->setWidth(233);
    body->setHeight(305);
    body->init();
    body->setParentItem(this);
    body->setZValue(1);
    body->setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    float centerX = (boundingRect().width()-body->getWidth())/2;
    body->setPos(QPointF(centerX,this->boundingRect().height()-6));

    container = new GridContainer(body);
    container->setVerticalAlignment(GridContainer::VerticalAlignment::TOP);
    container->setHorizontalAlignment(GridContainer::HorizontalAlignment::CENTER);
    container->setTopMargin(10);
    container->setVerticalSpacing(5);

    badge = new Badge(container,PENGUIN::BADGE::MEMBER_4);
    badge->setZValue(1);
    GridContainer::CELL_PROPERTIES* badge_CP = container->addGridItem(badge,0,0);
    badge_CP->horizontalAlignment = GridContainer::HorizontalAlignment::LEFT;

    username = new TextLabel();
    QFont font = username->getInput()->font();
    font.setPointSize(11);
    font.setBold(true);
    username->getInput()->setFont(font);
    username->setTextLimit(13);
    username->setText("WOWTHSIISALONGASDAK");
    username->setMaximumWidth(110);
    username->setMaximumHeight(container->getMaxHeight(0));
    container->addGridItem(username,0,1);

    CircleButton* xButton = new CircleButton();
    xButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/close/close.svg");
    GridContainer::CELL_PROPERTIES* xButton_CP = container->addGridItem(xButton,0,2);
    xButton_CP->horizontalAlignment = GridContainer::HorizontalAlignment::RIGHT;

    MultiCanvasObject* bg = new MultiCanvasObject();
    PROPERTIES* bg_properties = new PROPERTIES();
    bg_properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/playercard/background.svg";
    bg->initFrames(bg_properties->filePath,bg_properties);
    bg->setCurrentFrames(bg_properties);
    bg->setFrame(0);
    bg->setZValue(0);
    container->addGridItem(bg,1,0,3,1);

    penguin_paper = new PenguinPaper(bg);

    penguin_paper->changeColor("#fff");
    //417 403 443 413 474
    //penguin_paper->setFace(133);
    //penguin_paper->setHead(417);

    float pp_centerX = (bg->boundingRect().width()-penguin_paper->boundingRect().width())/2;
    float pp_centerY = (bg->boundingRect().height()-penguin_paper->boundingRect().height())-10;
    penguin_paper->setPos(QPointF(pp_centerX, pp_centerY));


    GridContainer* buttonsContainer = new GridContainer(container);
    buttonsContainer->setTopMargin(5);
    buttonsContainer->setHorizontalSpacing(5);

    CircleButton* friendButton = new CircleButton();
    friendButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/friend/friend.svg");
    buttonsContainer->addGridItem(friendButton,0,0);

    CircleButton* findButton = new CircleButton();
    findButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/help/help.svg");
    buttonsContainer->addGridItem(findButton,0,1);

    CircleButton* iglooButton = new CircleButton();
    iglooButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/igloo/igloo_disabled.svg");
    buttonsContainer->addGridItem(iglooButton,0,2);

    CircleButton* mailButton = new CircleButton();
    mailButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/mail/mail.svg");
    buttonsContainer->addGridItem(mailButton,0,3);

    CircleButton* stampButton = new CircleButton();
    stampButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/stamp/stamp.svg");
    buttonsContainer->addGridItem(stampButton,0,4);

    CircleButton* ignoreButton = new CircleButton();
    ignoreButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/ignore/ignore.svg");
    buttonsContainer->addGridItem(ignoreButton,0,5);

    CircleButton* reportButton = new CircleButton();
    reportButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/moderator/moderator.svg");
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
    inventory->setPenguinPaper(penguin_paper);
}

Inventory* PlayerCard::getInventory(){
    return inventory;
}
