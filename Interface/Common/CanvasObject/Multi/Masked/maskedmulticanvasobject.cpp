#include "maskedmulticanvasobject.h"

MaskedMultiCanvasObject::MaskedMultiCanvasObject(MultiCanvasObject* parent) : MultiCanvasObject(parent) {}

void MaskedMultiCanvasObject::setMask(QString filePath){

    QImage img = QImage(filePath);

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
    this->region = r;

}

void MaskedMultiCanvasObject::setMask(QRegion region){
    this->region = region;
    return;
}

QRegion& MaskedMultiCanvasObject::getRegion(){
    return region;
}

void MaskedMultiCanvasObject::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget){
    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;
    if(!region.isNull()){
        painter->setClipRegion(region);
    }
    QGraphicsSvgItem::paint(painter,&opts,widget);
}
