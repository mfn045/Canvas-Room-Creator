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
    body->setScale(1.1);
    body->setRow(7);
    body->setCol(5);
    body->init();
    body->setParentItem(this);
    body->setFlag(GraphicsItemFlag::ItemStacksBehindParent,true);
    float centerX = (boundingRect().width()-body->getWidth())/2;
    body->setPos(QPointF(centerX,this->boundingRect().height()-6));

    GridContainer* container = new GridContainer(body);
    container->setHorizontalSpacing(10);
    container->setVerticalSpacing(10);

    CanvasObject* labelParent = new CanvasObject();
    TextLabel* label = new TextLabel(labelParent);
    label->setText("Nickname");
    container->addGridItem(labelParent,0,0);
    label->getInput()->setStyleSheet("background-color:red;color:black;");

    BlueCircleButton* xButton = new BlueCircleButton();
    xButton->setIcon("C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/icons/ignore/ignore.svg");
    container->addGridItem(xButton,0,1);

    CanvasObject* bg = new CanvasObject();
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/playercard/background.svg";
    bg->initFrames(properties->filePath,properties);
    bg->setCurrentFrames(properties);
    bg->setFrame(0);

    container->addGridItem(bg,1,0,2,1);

    container->updateLayout();

    float bg_centerX = (body->getWidth()-container->getWidth())/2;
    float bg_centerY = (body->getHeight()-container->getHeight())/2;
    container->setPos(QPointF(bg_centerX,10));
}
