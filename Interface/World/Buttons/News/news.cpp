#include "news.h"

News::News(MultiCanvasObject* parent) : AbstractButton(parent) {
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.world.buttons.news.up"));
    setDown(am->getAssetPath("interface.world.buttons.news.down"));
    setOver(am->getAssetPath("interface.world.buttons.news.over"));

    notification = new MultiCanvasObject();
    notification->setParentItem(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = am->getAssetPath("interface.world.buttons.news.notification");
    notification->initFrames(properties->filePath,properties);
    notification->setCurrentFrames(properties);
    notification->setFrame(0);
    notification->setPos(QPointF(15,20));
}

void News::showNotification(){
    notification->show();
}

void News::hideNotification(){
    notification->show();
}
