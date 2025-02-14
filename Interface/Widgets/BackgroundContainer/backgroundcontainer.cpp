#include "backgroundcontainer.h"

BackgroundContainer::BackgroundContainer(float width, float height) {
    this->width = width;
    this->height = height;
}

void BackgroundContainer::init(){
    initialized = false;
    float offset = 0;
    rect = QRectF();
    /// Outermost box
    path = createPath(offset);
    rect = rect.united(path.boundingRect());
    /// White box
    offset = 2;
    path2 = createPath(offset);
    rect = rect.united(path2.boundingRect());
    /// #003366 box
    offset = 4;
    path3 = createPath(offset);
    rect = rect.united(path3.boundingRect());

    offset = 6;
    path4a = createPath(offset);
    rect = rect.united(path4a.boundingRect());

    offset = 6;
    path4b = createPath(offset,2);
    rect = rect.united(path4b.boundingRect());

    offset = 8;
    path5 = createPath(offset);
    rect = rect.united(path5.boundingRect());
    initialized = true;
}

float BackgroundContainer::setWidth(float width){
    this->initialized = false;
    this->width = width;
    return this->width;
}

float BackgroundContainer::getWidth(){
    return this->width;
}

float BackgroundContainer::setHeight(float height){
    this->initialized = false;
    this->height = height;
    return this->height;
}

float BackgroundContainer::getHeight(){
    return this->height;
}


void BackgroundContainer::setColor(BACKGROUNDCONTAINER::COLOR color){
    this->color = color;
    return;
}
BACKGROUNDCONTAINER::COLOR BackgroundContainer::getColor(){
    return this->color;
}

bool BackgroundContainer::hasBackdrop(){
    return this->backDrop;
}
bool BackgroundContainer::setHasBackdrop(bool backDrop){
    this->backDrop = backDrop;
    return this->backDrop;
}

void BackgroundContainer::setBackdropColor(QColor color){
    this->backDropColor = color;
}

void BackgroundContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(!initialized) return;
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setRenderHint(QPainter::LosslessImageRendering, true);


    if(scene() && backDrop){
        painter->save();
        QRectF sceneRect = scene()->sceneRect();
        QTransform sTransform = painter->deviceTransform();
        float xScale = sTransform.m11();
        float yScale = sTransform.m22();
        QTransform customTransform = QTransform(xScale,0,0,yScale,0,0);
        QRectF newRect = customTransform.mapRect(sceneRect);
        painter->setWindow(newRect.toRect());
        painter->setViewport(newRect.toRect());
        painter->setTransform(customTransform);
        painter->fillRect(newRect,QBrush(backDropColor));
        painter->restore();
    }

    painter->beginNativePainting();
    painter->save();
    QBrush brush = painter->brush();
    brush.setColor(QColor("white"));
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(0.49803922);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
    painter->restore();

    painter->save();
    brush = painter->brush();
    brush.setColor(QColor("white"));
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(1);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path2);
    painter->restore();

    painter->save();
    brush = painter->brush();
    if(color == BACKGROUNDCONTAINER::COLOR::BLUE){
        brush.setColor(QColor("#003366"));
    }else if(color == BACKGROUNDCONTAINER::COLOR::ORANGE){
        brush.setColor(QColor("#983901"));
    }
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(1);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path3);
    painter->restore();

    painter->save();
    brush = painter->brush();
    if(color == BACKGROUNDCONTAINER::COLOR::BLUE){
        brush.setColor(QColor("#006699"));
    }else if(color == BACKGROUNDCONTAINER::COLOR::ORANGE){
        brush.setColor(QColor("#c94b01"));
    }
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(1);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path4a);
    painter->restore();

    painter->save();
    brush = painter->brush();
    if(color == BACKGROUNDCONTAINER::COLOR::BLUE){
        brush.setColor(QColor("#00ccff"));
    }else if(color == BACKGROUNDCONTAINER::COLOR::ORANGE){
        brush.setColor(QColor("#ffcc00"));
    }
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(1);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path4b);
    painter->restore();

    painter->save();
    brush = painter->brush();
    brush.setColor(QColor("#0280cd"));
    if(color == BACKGROUNDCONTAINER::COLOR::BLUE){
        brush.setColor(QColor("#0280cd"));
    }else if(color == BACKGROUNDCONTAINER::COLOR::ORANGE){
        brush.setColor(QColor("#ff6600"));
    }
    brush.setStyle(Qt::SolidPattern);
    painter->setOpacity(1);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path5);
    painter->restore();
    painter->endNativePainting();
}

QPainterPath BackgroundContainer::createPath(float offset, float additionalShrink){
    //Box
    QPainterPath path;
    // Move Command
    path.moveTo(offset,44);
    // Vertical Line
    path.lineTo(offset,22);
    // Q Curve
    path.quadTo(offset,offset,22,offset);
    // Line Command
    path.lineTo(width-22,offset);
    // Q Curve
    path.quadTo(width-offset-additionalShrink,offset,width-offset-additionalShrink,22);
    // Line Command
    path.lineTo(width-offset-additionalShrink,height-22);
    // Q Curve
    path.quadTo(width-offset-additionalShrink,height-offset-additionalShrink,width-22,height-offset-additionalShrink);
    // Line Command
    path.lineTo(22,height-offset-additionalShrink);
    // Q Curve
    path.quadTo(offset,height-offset-additionalShrink,offset,height-22);
    // Line Command
    path.lineTo(offset,44);
    return path;
}

QRectF BackgroundContainer::boundingRect() const {
    return rect;
}
