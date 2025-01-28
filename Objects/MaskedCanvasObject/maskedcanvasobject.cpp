#include "maskedcanvasobject.h"

MaskedCanvasObject::MaskedCanvasObject(CanvasObject* parent) : CanvasObject(parent) {}

void MaskedCanvasObject::setMask(QString filePath){

    QPixmap item(filePath);

    QImage img = item.toImage();

    QRegion r;
    qDebug() << r;
    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            QColor color = img.pixelColor(x, y);
            if (color.alpha() > 0) {
                r += QRect(x, y, 1, 1);
            }
        }
    }
    qDebug() << r;
    region = r;
}

QRegion& MaskedCanvasObject::getRegion(){
    return region;
}

void MaskedCanvasObject::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    if(!region.isNull()){
        painter->setClipRegion(region);
    }
    return QGraphicsSvgItem::paint(painter,option,widget);
}
