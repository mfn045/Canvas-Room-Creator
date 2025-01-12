#include "playercard.h"

PlayerCard::PlayerCard(Scene* scene) {
    if(scene != nullptr){
        this->scene = scene;
    }
    setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/rectbuttonstripes/rectbuttonstripes.svg");
    setPos(QPointF(100,100));
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setIsClickable(true);
    setIsHoverable(true);

    body = new DialogGrid(scene);
    body->setWidth(230);
    body->setHeight(300);
    body->init();
    body->setParentItem(this);
    body->setZValue(1);
    body->setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    float centerX = (boundingRect().width()-body->getWidth())/2;
    body->setPos(QPointF(centerX,this->boundingRect().height()-6));

    GridContainer* container = new GridContainer(body);
    container->setVerticalSpacing(5);

    CanvasObject* band = new CanvasObject();
    PROPERTIES* bandProperties = new PROPERTIES();
    bandProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/player/band_0.svg";
    band->initFrames(bandProperties->filePath,bandProperties);
    band->setCurrentFrames(bandProperties);
    band->setFrame(0);
    band->setScale(2);
    band->setZValue(1);
    container->addGridItem(band,0,0);

    TextLabel* label = new TextLabel();
    QFont font = label->getInput()->font();
    font.setPointSize(11);
    font.setBold(true);
    label->getInput()->setFont(font);
    label->setTextLimit(13);
    label->setText("Nic");
    label->setMaximumWidth(110);
    label->setMaximumHeight(container->getMaxHeight(0));
    container->addGridItem(label,0,1);
    container->setMaxWidth(1,110);

    CircleButton* xButton = new CircleButton();
    xButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/close/close.svg");
    container->addGridItem(xButton,0,2);

    CanvasObject* bg = new CanvasObject();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/playercard/background.svg";
    bg->initFrames(properties->filePath,properties);
    bg->setCurrentFrames(properties);
    bg->setFrame(0);
    bg->setZValue(0);
    container->addGridItem(bg,1,0,3,1);

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


    container->updateLayout();

    float bg_centerX = (body->getWidth()-container->getWidth())/2;
    float bg_centerY = (body->getHeight()-container->getHeight())/2;
    container->setPos(QPointF(bg_centerX,bg_centerY));


    CanvasObject* inventory = new CanvasObject(this);
    PROPERTIES* invProperties = new PROPERTIES();
    invProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/playercard/inventory/inventory.svg";
    inventory->setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    inventory->initFrames(invProperties->filePath,invProperties);
    inventory->setCurrentFrames(invProperties);
    inventory->setFrame(0);
    inventory->setZValue(0);
    QTransform invTransform = inventory->transform();
    invTransform.setMatrix(0.975,invTransform.m12(),invTransform.m13(),
                            invTransform.m21(),0.975,invTransform.m23(),
                            invTransform.m31(),invTransform.m32(),invTransform.m33());
    inventory->setTransform(invTransform);
    inventory->setPos(QPointF(50,boundingRect().height()-5));


    GridContainer* items = new GridContainer(inventory);
    items->setTopMargin(20);
    items->setVerticalSpacing(5);
    items->setHorizontalSpacing(5);
    items->setHorizontalAlignment(GridContainer::HorizontalAlignment::RIGHT);
    items->setScale(0.975);
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 3; c++){
            items->addGridItem(new WhiteSquareButton(nullptr,WhiteSquareButton::SIZE::MEDIUM),r,c);
        }
    }
    CanvasObject* scrollBar = new CanvasObject();
    PROPERTIES* scrollBarProperties = new PROPERTIES();
    scrollBarProperties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/whitescrollrect/whitescrollrect.svg";
    scrollBar->initFrames(scrollBarProperties->filePath,scrollBarProperties);
    scrollBar->setCurrentFrames(scrollBarProperties);
    scrollBar->setFrame(0);

    items->addGridItem(scrollBar,0,3,1,4);

    CircleButton* scrollUpButton = new CircleButton(scrollBar,CircleButton::COLOR::WHITE);
    scrollUpButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/whitearrows/up/up.svg");
    scrollUpButton->setPos(QPointF(0,-(scrollUpButton->boundingRect().height()/2)));

    CircleButton* scrollDownButton = new CircleButton(scrollBar,CircleButton::COLOR::WHITE);
    scrollDownButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/whitearrows/down/down.svg");
    scrollDownButton->setPos(QPointF(0,scrollBar->boundingRect().height()-(scrollUpButton->boundingRect().height()/2)));

    items->updateLayout();
}
