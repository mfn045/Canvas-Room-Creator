#include "clothingitem.h"

ClothingItem::ClothingItem(CanvasObject* parent) : CanvasObject(parent) {
    //viewBox="0 -40 0.001 50";
}

void ClothingItem::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget){
    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;
    renderer()->setViewBox(QRectF(-30,-30,50,50));

    QGraphicsSvgItem::paint(painter,&opts,widget);
}

void ClothingItem::updateViewbox(){
    QDomDocument doc;
    for(auto it = getFrames().begin(); it != getFrames().end(); it++){
        for(QByteArray* ba : it.value()){
            doc.setContent(*ba);
            QDomElement docElement = doc.documentElement();
            if(!docElement.isNull()){
                docElement.setAttribute("viewBox","0 -40 0.001 50");
            }
            *ba = doc.toByteArray();
            qDebug() << " DOC EDITED " << *ba;
        }
    }
}
