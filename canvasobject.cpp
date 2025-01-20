#include "canvasobject.h"


CanvasObject::CanvasObject(CanvasObject* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    //setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setFlag(GraphicsItemFlag::ItemClipsToShape);
    //setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
    if(parent != nullptr && !parent->getOrigin().isNull()){
        setOrigin(parent->getOrigin());
    }
}

CanvasObject::CanvasObject(QString dir, CanvasObject* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    //setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setFlag(GraphicsItemFlag::ItemClipsToShape);
    //setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
    if(parent != nullptr && !parent->getOrigin().isNull()){
        setOrigin(parent->getOrigin());
    }
}

bool CanvasObject::isTransparentPixel(QPointF pos){
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

void CanvasObject::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mousePress(event->pos());
    }
    return QGraphicsObject::mousePressEvent(event);
}

void CanvasObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mouseMove(event->pos());
    }
    return QGraphicsObject::mouseMoveEvent(event);
}

void CanvasObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit mouseRelease(event->pos());
    }
    return QGraphicsObject::mouseReleaseEvent(event);
}

void CanvasObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit hoverEnter(event->pos());
    }
    return QGraphicsObject::hoverEnterEvent(event);
}

void CanvasObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    if(containsActionFlag(ACTION::CLICKABLE) && !isTransparentPixel(event->pos())){
        setCursor(Qt::PointingHandCursor);
        emit hoverMove(event->pos());
    }else if(containsActionFlag(ACTION::CLICKABLE) && isTransparentPixel(event->pos())){
        setCursor(Qt::ArrowCursor);
    }
    return QGraphicsObject::hoverMoveEvent(event);
}

void CanvasObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(!isTransparentPixel(event->pos())){
        emit hoverLeave(event->pos());
    }
    return QGraphicsObject::hoverLeaveEvent(event);
}


CanvasObject::CONST_POSITION CanvasObject::setConstPosition(CONST_POSITION newConst){
    this->posConst = newConst;
    return this->posConst;
}

CanvasObject::CONST_POSITION CanvasObject::getConstPosition(){
    return this->posConst;
}

bool CanvasObject::isClickable(){
    return containsActionFlag(ACTION::CLICKABLE);
}

bool CanvasObject::setIsClickable(bool isClickable){
    if(isClickable){
        setActionFlags(getActionFlags() | ACTION::CLICKABLE);
    }else{
        setActionFlags(getActionFlags() & ~ACTION::CLICKABLE);
    }
    return containsActionFlag(ACTION::CLICKABLE);
}

bool CanvasObject::isHoverable(){
    return containsActionFlag(ACTION::HOVERABLE);
}

bool CanvasObject::setIsHoverable(bool isClickable){
    if(isClickable){
        setAcceptHoverEvents(true);
        setActionFlags(getActionFlags() | ACTION::HOVERABLE);
    }else{
        setAcceptHoverEvents(false);
        setActionFlags(getActionFlags() & ~ACTION::HOVERABLE);
    }
    return containsActionFlag(ACTION::HOVERABLE);
}

bool CanvasObject::isMouseTrackable(){
    return containsActionFlag(ACTION::MOUSE_TRACKABLE);
}

bool CanvasObject::setIsMouseTrackable(bool mouseTrackable){
    if(mouseTrackable){
        setActionFlags(getActionFlags() | ACTION::MOUSE_TRACKABLE);
    }else{
        setActionFlags(getActionFlags() & ~ACTION::MOUSE_TRACKABLE);
    }
    return containsActionFlag(ACTION::MOUSE_TRACKABLE);
}

void CanvasObject::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget){
    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;

    QGraphicsSvgItem::paint(painter,&opts,widget);
}

QVariant CanvasObject::itemChange(GraphicsItemChange change, const QVariant &value){
    if(change == GraphicsItemChange::ItemPositionChange && !isSettingFrame && !this->currentFrames.isEmpty()){
        QPointF pos = value.toPointF();
        QSvgRenderer rend(*this->currentFrames.at(0));
        QSize size = rend.defaultSize();
        pos.setX(pos.x()+size.width()/2);
        pos.setY(pos.y()+size.height()/2);
        getCurrentProperties()->xOffset=pos.x()-getOrigin().x();
        getCurrentProperties()->yOffset=pos.y()-getOrigin().y();
    }
    return QGraphicsSvgItem::itemChange(change,value);
}

void CanvasObject::initFrames(QString filePath,PROPERTIES* properties){
    if(filePath.isEmpty()) return;
    QList<QByteArray*> arrays;
    if(filePath.contains(".svg")){
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
            return;
        QByteArray* byte = new QByteArray(file.readAll());
        arrays.append(byte);
        file.close();
        if(frames.contains(properties)){
            for(QByteArray* map : frames.value(properties)){
                delete map;
            }
            frames.remove(properties);
        }
        frames.insert(properties,arrays);
    }else{
        QDir directory(filePath,"*.svg",QDir::SortFlag::Name);
        QStringList list = directory.entryList();
        QCollator collator;
        collator.setNumericMode(true);
        std::sort(list.begin(), list.end(), collator);

        for(QString fileName : list){
            QFile file(filePath + "/" + fileName);
            if (file.open(QIODevice::ReadOnly)){
                QByteArray* byte = new QByteArray(file.readAll());
                arrays.append(byte);
                file.close();
            }
        }
        if(frames.contains(properties)){
            for(QByteArray* map : frames.value(properties)){
                delete map;
            }
            frames.remove(properties);
        }
        frames.insert(properties,arrays);
    }
}

QPointF CanvasObject::getOrigin(){
    return this->origin;
}

QPointF CanvasObject::setOrigin(QPointF origin){
    this->origin = origin;
    QList<QGraphicsItem*> children = childItems();
    for(QGraphicsItem* child : children){
        CanvasObject* childObj = (CanvasObject*)child;
        childObj->setOrigin(this->origin);
    }
    return this->origin;
}

QString CanvasObject::getName(){
    return this->name;
}

QString CanvasObject::setName(QString name){
    this->name=name;
    return this->name;
}


int CanvasObject::getID(){
    return this->id;
}

int CanvasObject::setID(int id){
    this->id=id;
    return this->id;
}

QList<QByteArray*>& CanvasObject::setCurrentFrames(PROPERTIES* paramProperties){
    bool changed = false;
    isSettingFrame = true;
    for(PROPERTIES* properties : frames.keys()){
        if(properties != nullptr && properties == paramProperties){
            this->currentFrames = frames.value(properties);
            this->currentProperties = properties;
            changed = true;
        }
    }
    if(!changed){
        QList<QByteArray*> map;
        map.append(new QByteArray("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"100\"></svg>"));
        this->currentFrames = map;
    }
    isSettingFrame = false;
    return this->currentFrames;
}


QList<QByteArray*>& CanvasObject::getCurrentFrames(){
    return this->currentFrames;
}

int CanvasObject::getCurrentFrame(){
    return this->currentFrame;
}

bool CanvasObject::isFramePaused(){
    if(framePauses.contains(currentFrame)){
        return true;
    }
    return false;
}


QMap<CanvasObject::PROPERTIES*, QList<QByteArray*>>& CanvasObject::getFrames(){
    return this->frames;
}


bool CanvasObject::hasAnimationLoop(){
    return this->animationLoop;
}

bool CanvasObject::setHasAnimationLoop(bool animationLoop){
    this->animationLoop = animationLoop;
    return this->animationLoop;
}

bool CanvasObject::isAnimationOn(){
    return this->animationOn;
}

bool CanvasObject::setIsAnimationOn(bool animationOn){
    this->animationOn = animationOn;
    return this->animationOn;
}


void CanvasObject::nextFrame(bool loop, bool force){
    if(currentFrames.isEmpty()) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(!animationOn) return;
    if(currentFrame < currentFrames.size()-1){
        currentFrame++;
        renderer()->load(*currentFrames.at(currentFrame));
        setElementId("");
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<CanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->renderer()->load(*obj->currentFrames.at(currentFrame));
                        obj->setElementId("");
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=0;
            renderer()->load(*currentFrames.at(currentFrame));
            setElementId("");
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<CanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->renderer()->load(*obj->currentFrames.at(currentFrame));
                            obj->setElementId("");
                        }
                    }
                }
            }
            isImageLatest = false;
        }else{
            emit animationDone();
        }
    }
}

void CanvasObject::setFrame(int currentFrame){
    if(currentFrames.isEmpty()) return;
    if(currentFrame < currentFrames.size() && currentFrame >= 0){
        this->currentFrame = currentFrame;
        renderer()->load(*currentFrames.at(currentFrame));
        setElementId("");
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<CanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->renderer()->load(*obj->currentFrames.at(currentFrame));
                        obj->update();
                        obj->setElementId("");
                    }
                }
            }
        }
        isImageLatest = false;
    }
}

void CanvasObject::prevFrame(bool loop, bool force){
    if(currentFrames.isEmpty()) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(!animationOn) return;
    if(currentFrame > 0){
        currentFrame--;
        renderer()->load(*currentFrames.at(currentFrame));
        setElementId("");
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<CanvasObject*>(child)){
                    if(currentFrame < obj->currentFrames.size()) {
                        obj->currentFrame = currentFrame;
                        obj->renderer()->load(*obj->currentFrames.at(currentFrame));
                        obj->setElementId("");
                    }
                }
            }
        }
        isImageLatest = false;
    }else{
        if(loop){
            currentFrame=currentFrames.size()-1;
            renderer()->load(*currentFrames.at(currentFrame));
            setElementId("");
            QList<QGraphicsItem*> children = childItems();
            if(children.size() > 0){
                for(QGraphicsItem* child : children){
                    if(auto obj = dynamic_cast<CanvasObject*>(child)){
                        if(currentFrame < obj->currentFrames.size()) {
                            obj->currentFrame = currentFrame;
                            obj->renderer()->load(*obj->currentFrames.at(currentFrame));
                            obj->update();
                            obj->setElementId("");
                        }
                    }
                }
            }
            isImageLatest = false;
        }else{
            emit animationDone();
        }
    }
}

CanvasObject::PROPERTIES* CanvasObject::getCurrentProperties(){
    return this->currentProperties;
}

int CanvasObject::getActionFlags(){
    return actionFlags;
}

bool CanvasObject::containsActionFlag(ACTION flag){
    if((actionFlags & flag) != 0){
        return true;
    }
    return false;
}

void CanvasObject::setActionFlags(int flags){
    actionFlags = flags;
}
