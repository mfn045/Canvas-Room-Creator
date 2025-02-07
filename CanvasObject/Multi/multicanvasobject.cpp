#include "multicanvasobject.h"



MultiCanvasObject::MultiCanvasObject(MultiCanvasObject* parent) : AbstractCanvasObject(parent) {
    if(parent != nullptr && !parent->getOrigin().isNull()){
        setOrigin(parent->getOrigin());
    }
}

MultiCanvasObject::~MultiCanvasObject(){
    clearFrames();
    qDebug() << "DELETED CANVAS!";
}

void MultiCanvasObject::refresh(){
    setCurrentFrames(getCurrentProperties());
    setFrame(getCurrentFrame());
    return;
}

MultiCanvasObject::CONST_POSITION MultiCanvasObject::setConstPosition(CONST_POSITION newConst){
    this->posConst = newConst;
    return this->posConst;
}

MultiCanvasObject::CONST_POSITION MultiCanvasObject::getConstPosition(){
    return this->posConst;
}


void MultiCanvasObject::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget){
    QStyleOptionGraphicsItem opts(*option);

    opts.state &= ~QStyle::State_Selected;

    QGraphicsSvgItem::paint(painter,&opts,widget);
}

QVariant MultiCanvasObject::itemChange(GraphicsItemChange change, const QVariant &value){
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

void MultiCanvasObject::initFrames(QString filePath,PROPERTIES* properties){
    if(filePath.isEmpty()) return;
    if(!QFile(filePath).exists()){
        filePath = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/unknown/1.svg";
        properties->filePath = filePath;
    }
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


void MultiCanvasObject::clearFrames(){
    for(auto i = frames.begin(); i != frames.end(); i++){
        PROPERTIES* properties = i.key();
        QList<QByteArray*> arrs = i.value();
        for(auto j = arrs.begin(); j != arrs.end(); j++){
            QByteArray* byte = *j;
            byte->clear();
            delete byte;
        }
        arrs.clear();
        delete properties;
    }
    frames.clear();
    currentFrames.clear();
    currentProperties = nullptr;
    currentFrame = 0;
    setPos(0,0);
    renderer()->load(QByteArray("<svg width=\"0px\" height=\"0px\"></svg>"));
    setElementId("");
}

QList<QByteArray*>& MultiCanvasObject::setCurrentFrames(PROPERTIES* paramProperties){
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


QList<QByteArray*>& MultiCanvasObject::getCurrentFrames(){
    return this->currentFrames;
}


QMap<MultiCanvasObject::PROPERTIES*, QList<QByteArray*>>& MultiCanvasObject::getFrames(){
    return this->frames;
}

void MultiCanvasObject::nextFrame(bool loop, bool force){
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
                if(auto obj = dynamic_cast<MultiCanvasObject*>(child)){
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
                    if(auto obj = dynamic_cast<MultiCanvasObject*>(child)){
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

void MultiCanvasObject::setFrame(int currentFrame){
    if(currentFrames.isEmpty()) return;
    if(currentFrame < currentFrames.size() && currentFrame >= 0){
        this->currentFrame = currentFrame;
        renderer()->load(*currentFrames.at(currentFrame));
        setElementId("");
        QList<QGraphicsItem*> children = childItems();
        if(children.size() > 0){
            for(QGraphicsItem* child : children){
                if(auto obj = dynamic_cast<MultiCanvasObject*>(child)){
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

void MultiCanvasObject::prevFrame(bool loop, bool force){
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
                if(auto obj = dynamic_cast<MultiCanvasObject*>(child)){
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
                    if(auto obj = dynamic_cast<MultiCanvasObject*>(child)){
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

MultiCanvasObject::PROPERTIES* MultiCanvasObject::getCurrentProperties(){
    return this->currentProperties;
}
