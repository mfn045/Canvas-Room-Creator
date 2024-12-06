#include "canvasobject.h"



CanvasObject::CanvasObject(CanvasObject* obj){
    CanvasObject(obj->getFilePath());
}

CanvasObject::CanvasObject(QString filePath) {
    objectProperties = new PROPERTIES();
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setPos(QPointF(100,100));
    initFrames(filePath);
    setCurrentFrames();
    setFrame(getCurrentFrame());

}

void CanvasObject::initFrames(QString filePath,DIRECTION direction,STATE state){
    PROPERTIES* properties = new PROPERTIES();
    properties->currentDirection=direction;
    properties->currentState=state;

    this->filePath = filePath;
    QList<QPixmap>* pixmaps = new QList<QPixmap>();
    if(filePath.contains(".png") || filePath.contains(".svg")){
        qDebug() << filePath;
        pixmaps->append(QPixmap(filePath));
        frames.insert(properties,pixmaps);

    }else{
        QDir directory(filePath,"*.png",QDir::SortFlag::Name);
        qDebug() << directory;
        QStringList list = directory.entryList();
        QCollator collator;
        collator.setNumericMode(true);
        std::sort(list.begin(), list.end(), collator);

        for(QString fileName : list){
            pixmaps->append(QPixmap(filePath + "/" + fileName));
        }
        frames.insert(properties,pixmaps);
    }
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

QString CanvasObject::getFilePath(){
    return this->filePath;
}

QList<QPixmap>* CanvasObject::setCurrentFrames(DIRECTION direction,STATE state){
    for(PROPERTIES* properties : frames.keys()){
        if(properties->currentDirection == direction && properties->currentState == state){
            this->currentFrames = frames.value(properties);
        }
    }
}


QList<QPixmap>* CanvasObject::getCurrentFrames(DIRECTION direction,STATE state){
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

void CanvasObject::nextFrame(bool loop, bool force){
    if(currentFrames == nullptr) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(currentFrame < currentFrames->size()-1){
        currentFrame++;
        setPixmap(currentFrames->at(currentFrame));
    }else{
        currentFrame=0;
        setPixmap(currentFrames->at(currentFrame));
    }
}


void CanvasObject::setFrame(int currentFrame){
    if(currentFrames == nullptr) return;
    if(currentFrame < currentFrames->size() && currentFrame >= 0){
        this->currentFrame = currentFrame;
        setPixmap(currentFrames->at(currentFrame));
    }
}
void CanvasObject::prevFrame(bool loop, bool force){
    if(currentFrames == nullptr) return;
    if(framePauses.contains(currentFrame) && !force) return;
    if(currentFrame > 0){
        currentFrame--;
        setPixmap(currentFrames->at(currentFrame));
    }else{
        if(loop){
            currentFrame=currentFrames->size()-1;
            setPixmap(currentFrames->at(currentFrame));
        }
    }
}
