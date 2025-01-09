#include "news.h"

News::News(CanvasObject* parent) : AbstractButton(parent) {
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);

    notification = new CanvasObject();
    notification->setParentItem(this);
    PROPERTIES* properties = new PROPERTIES();
    properties->filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/news/notification.svg";
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
