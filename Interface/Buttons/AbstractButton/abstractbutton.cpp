#include "abstractbutton.h"

AbstractButton::AbstractButton(CanvasObject *parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable);

    if(parent != nullptr){
        setParentItem(parent);
    }
}


QVariant AbstractButton::positionChanged(const QVariant& pos){
    return pos;
}

QVariant AbstractButton::itemChange(GraphicsItemChange change, const QVariant &value){
     if(change == GraphicsItemChange::ItemPositionChange){
        return positionChanged(value);
    }
    return QGraphicsObject::itemChange(change,value);
}

void AbstractButton::setUp(QString filePath){
    BUTTONPROPERTIES* upProperties = new BUTTONPROPERTIES();
    upProperties->filePath = filePath;
    upProperties->state = STATE::UP;
    initFrames(upProperties->filePath,upProperties);
    if(!initialized && isClickable()){
        setCurrentFrames(STATE::UP);
        setFrame(0);
    }
}
void AbstractButton::setDown(QString filePath){
    BUTTONPROPERTIES* downProperties = new BUTTONPROPERTIES();
    downProperties->filePath = filePath;
    downProperties->state = STATE::DOWN;
    initFrames(downProperties->filePath,downProperties);
}
void AbstractButton::setOver(QString filePath){
    BUTTONPROPERTIES* overProperties = new BUTTONPROPERTIES();
    overProperties->filePath = filePath;
    overProperties->state = STATE::OVER;
    initFrames(overProperties->filePath,overProperties);
    if(!initialized && !isClickable()){
        setCurrentFrames(STATE::UP);
        setFrame(0);
    }
}

CanvasObject* AbstractButton::getIcon(){
    return this->icon;
}

CanvasObject* AbstractButton::setIcon(QString filePath){
    PROPERTIES* properties = new PROPERTIES();
    if(icon == nullptr){
        icon = new CanvasObject();
        icon->setParentItem(this);
    }
    properties->filePath = filePath;
    icon->initFrames(properties->filePath,properties);
    icon->setCurrentFrames(properties);
    icon->setFrame(0);
    return icon;
}

void AbstractButton::setCurrentFrames(STATE state){
    bool changed = false;
    for(PROPERTIES* properties : getFrames().keys()){
        BUTTONPROPERTIES* buttonProperties = (BUTTONPROPERTIES*) properties;
        if(buttonProperties->state == state){
            CanvasObject::setCurrentFrames(properties);
            changed = true;
        }
    }
    if(changed){
        this->currentState = state;
    }
}


void AbstractButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(boundingRect().contains(event->pos()) && !isTransparentPixel(event->pos())){
        int oldHeight = boundingRect().height();
        setCurrentFrames(STATE::DOWN);
        setFrame(0);
        int newHeight = boundingRect().height();
        if(oldHeight != newHeight && getConstPosition() == BOTTOM){
            QPointF currentPos = pos();
            currentPos.setY(currentPos.y()-(newHeight-oldHeight));
            setPos(currentPos);
        }
        emit clicked();
    }
    return QGraphicsObject::mousePressEvent(event);
}

void AbstractButton::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit mouseMove(event->scenePos());
    return QGraphicsObject::mouseMoveEvent(event);
}
void AbstractButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(boundingRect().contains(event->pos()) && !isTransparentPixel(event->pos())){
        int oldHeight = boundingRect().height();
        setCurrentFrames(STATE::OVER);
        setFrame(0);
        int newHeight = boundingRect().height();
        if(oldHeight != newHeight && getConstPosition() == BOTTOM){
            QPointF currentPos = pos();
            currentPos.setY(currentPos.y()-(newHeight-oldHeight));
            setPos(currentPos);
        }
    }
    return QGraphicsObject::mouseReleaseEvent(event);
}

void AbstractButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(currentState != STATE::UP){
        int oldHeight = boundingRect().height();
        setCurrentFrames(STATE::UP);
        setFrame(0);
        int newHeight = boundingRect().height();
        if(oldHeight != newHeight && getConstPosition() == BOTTOM){
            QPointF currentPos = pos();
            currentPos.setY(currentPos.y()-(newHeight-oldHeight));
            setPos(currentPos);
        }
    }
    return QGraphicsObject::hoverLeaveEvent(event);
}

void AbstractButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(currentState != STATE::OVER){
        int oldHeight = boundingRect().height();
        setCurrentFrames(STATE::OVER);
        setFrame(0);
        int newHeight = boundingRect().height();
        if(oldHeight != newHeight && getConstPosition() == BOTTOM){
            QPointF currentPos = pos();
            currentPos.setY(currentPos.y()-(newHeight-oldHeight));
            setPos(currentPos);
        }
    }
    return QGraphicsObject::hoverLeaveEvent(event);
}
