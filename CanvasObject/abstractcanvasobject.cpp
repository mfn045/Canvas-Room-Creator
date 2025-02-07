#include "abstractcanvasobject.h"

AbstractCanvasObject::AbstractCanvasObject(AbstractCanvasObject* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    //setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setFlag(GraphicsItemFlag::ItemClipsToShape);
    //setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
}


QPointF AbstractCanvasObject::getOrigin(){
    return this->origin;
}
QPointF AbstractCanvasObject::setOrigin(QPointF origin){
    this->origin = origin;
    QList<QGraphicsItem*> children = childItems();
    for(QGraphicsItem* child : children){
        AbstractCanvasObject* childObj = (AbstractCanvasObject*)child;
        childObj->setOrigin(this->origin);
    }
    return this->origin;
}

bool AbstractCanvasObject::isFramePaused(){
    if(framePauses.contains(currentFrame)){
        return true;
    }
    return false;
}

void AbstractCanvasObject::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mousePress(event->pos());
    }
    return QGraphicsObject::mousePressEvent(event);
}

void AbstractCanvasObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mouseMove(event->pos());
    }
    return QGraphicsObject::mouseMoveEvent(event);
}

void AbstractCanvasObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mouseRelease(event->pos());
    }
    return QGraphicsObject::mouseReleaseEvent(event);
}

void AbstractCanvasObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit hoverEnter(event->pos());
    }
    return QGraphicsObject::hoverEnterEvent(event);
}

void AbstractCanvasObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << isTransparentPixel(event->pos());
    if(containsActionFlag(CANVAS::ACTION::CLICKABLE) && !isTransparentPixel(event->pos())){
        setCursor(Qt::PointingHandCursor);
        emit hoverMove(event->pos());
    }else if(containsActionFlag(CANVAS::ACTION::CLICKABLE) && isTransparentPixel(event->pos())){
        setCursor(Qt::ArrowCursor);
    }
    return QGraphicsObject::hoverMoveEvent(event);
}

void AbstractCanvasObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit hoverLeave(event->pos());
    }
    return QGraphicsObject::hoverLeaveEvent(event);
}

bool AbstractCanvasObject::isClickable(){
    return containsActionFlag(CANVAS::ACTION::CLICKABLE);
}

bool AbstractCanvasObject::setIsClickable(bool isClickable){
    if(isClickable){
        setActionFlags(getActionFlags() | CANVAS::ACTION::CLICKABLE);
    }else{
        setActionFlags(getActionFlags() & ~CANVAS::ACTION::CLICKABLE);
    }
    return containsActionFlag(CANVAS::ACTION::CLICKABLE);
}

bool AbstractCanvasObject::isHoverable(){
    return containsActionFlag(CANVAS::ACTION::HOVERABLE);
}

bool AbstractCanvasObject::setIsHoverable(bool isClickable){
    if(isClickable){
        setAcceptHoverEvents(true);
        setActionFlags(getActionFlags() | CANVAS::ACTION::HOVERABLE);
    }else{
        setAcceptHoverEvents(false);
        setActionFlags(getActionFlags() & ~CANVAS::ACTION::HOVERABLE);
    }
    return containsActionFlag(CANVAS::ACTION::HOVERABLE);
}

bool AbstractCanvasObject::isMouseTrackable(){
    return containsActionFlag(CANVAS::ACTION::MOUSE_TRACKABLE);
}

bool AbstractCanvasObject::setIsMouseTrackable(bool mouseTrackable){
    if(mouseTrackable){
        setActionFlags(getActionFlags() | CANVAS::ACTION::MOUSE_TRACKABLE);
    }else{
        setActionFlags(getActionFlags() & ~CANVAS::ACTION::MOUSE_TRACKABLE);
    }
    return containsActionFlag(CANVAS::ACTION::MOUSE_TRACKABLE);
}

bool AbstractCanvasObject::isTransparentPixel(QPointF pos){
    if(!isImageLatest){
        QSvgRenderer* renderer = this->renderer();
        if(image == nullptr){
            image = std::make_unique<QImage>(renderer->defaultSize(), QImage::Format_ARGB32);
            QPainter painter(image.get());
            renderer->render(&painter);
            isImageLatest = true;
        }else{
            image.release();
            image = std::make_unique<QImage>(renderer->defaultSize(), QImage::Format_ARGB32);
            QPainter painter(image.get());
            renderer->render(&painter);
            isImageLatest = true;
        }
    }
    if (image != nullptr){
        if (image->rect().contains(pos.toPoint())) {
            QColor pixelColor = image->pixelColor(pos.toPoint());
            if (pixelColor.alpha() == 0) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool AbstractCanvasObject::hasAnimationLoop(){
    return this->animationLoop;
}

bool AbstractCanvasObject::setHasAnimationLoop(bool animationLoop){
    this->animationLoop = animationLoop;
    return this->animationLoop;
}

bool AbstractCanvasObject::isAnimationOn(){
    return this->animationOn;
}

bool AbstractCanvasObject::setIsAnimationOn(bool animationOn){
    this->animationOn = animationOn;
    return this->animationOn;
}


int AbstractCanvasObject::getActionFlags(){
    return actionFlags;
}

bool AbstractCanvasObject::containsActionFlag(CANVAS::ACTION flag){
    if((actionFlags & flag) != 0){
        return true;
    }
    return false;
}

void AbstractCanvasObject::setActionFlags(int flags){
    actionFlags = flags;
}


QString AbstractCanvasObject::getName(){
    return this->name;
}

QString AbstractCanvasObject::setName(QString name){
    this->name=name;
    return this->name;
}

int AbstractCanvasObject::getCurrentFrame(){
    return this->currentFrame;
}

int AbstractCanvasObject::getID(){
    return this->id;
}

int AbstractCanvasObject::setID(int id){
    this->id=id;
    return this->id;
}
