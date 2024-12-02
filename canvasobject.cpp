#include "canvasobject.h"



CanvasObject::CanvasObject(CanvasObject* obj){
    CanvasObject(obj->getFilePath());
    setFrame(obj->getCurrentFrame());
}

CanvasObject::CanvasObject(QString filePath) {
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setPos(QPointF(100,100));
    this->filePath = filePath;
    if(filePath.contains(".png") || filePath.contains(".svg")){
        qDebug() << filePath;
        frames.append(QPixmap(filePath));
    }else{
        QDir directory(filePath,"*.png",QDir::SortFlag::Name);
        qDebug() << directory;
        QStringList list = directory.entryList();
        QCollator collator;
        collator.setNumericMode(true);
        std::sort(list.begin(), list.end(), collator);

        for(QString fileName : list){
            frames.append(QPixmap(filePath + "/" + fileName));
        }
    }
    setFrame(0);
    qDebug() << frames;

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


int CanvasObject::getCurrentFrame(){
    return this->frame;
}

void CanvasObject::nextFrame(){
    if(frame < frames.size()-1){
        frame++;
        setPixmap(frames.at(frame));
    }else{
        frame=0;
        setPixmap(frames.at(frame));
    }
}


void CanvasObject::setFrame(int frame){
    if(frame < frames.size() && frame >= 0){
        this->frame = frame;
        setPixmap(frames.at(frame));
    }
}
void CanvasObject::prevFrame(){
    if(frame > 0){
        frame--;
        setPixmap(frames.at(frame));
    }
}

QList<QPixmap> CanvasObject::getFrames(){
    return this->frames;
}
