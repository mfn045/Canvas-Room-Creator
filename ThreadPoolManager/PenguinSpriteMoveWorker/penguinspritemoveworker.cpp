#include "penguinspritemoveworker.h"

PenguinSpriteMoveWorker::PenguinSpriteMoveWorker() { setAutoDelete(true); }

bool PenguinSpriteMoveWorker::hasStarted(){
    return this->started;
}

void PenguinSpriteMoveWorker::run(){
    this->started = true;
    while(!movingSprites.empty()){
        for(auto i = movingSprites.begin(); i != movingSprites.end(); i++){
            AbstractCanvasObject* sprite = i.key();
            QPointF destination = i.value();
            if(sprite->pos() != destination){
                QPointF before = sprite->pos();
                double x_add = 1;
                double y_add = 1;
                if(before.x() > destination.x()){
                    x_add*=-1;
                }
                if(before.y() > destination.y()){
                    y_add*=-1;
                }

                double y_diff = destination.y() - before.y();
                double x_diff = destination.x() - before.x();
                double length = sqrt(pow(y_diff,2)+pow(x_diff,2));
                double normalized_y = y_diff/length;
                double normalized_x = x_diff/length;
                double velocity = 7;
                if(before.x() != destination.x()){
                    before.setX(before.x()+normalized_x*velocity);
                    if(x_add == 1){
                        if(before.x() > destination.x()){
                            before.setX(destination.x());
                        }
                    }else if(x_add == -1){
                        if(before.x() < destination.x()){
                            before.setX(destination.x());
                        }
                    }
                }
                if(before.y() != destination.y()){
                    before.setY(before.y()+normalized_y*velocity);
                    if(y_add == 1){
                        if(before.y() > destination.y()){
                            before.setY(destination.y());
                        }
                    }else if(y_add == -1){
                        if(before.y() < destination.y()){
                            before.setY(destination.y());
                        }
                    }
                }
                QMetaObject::invokeMethod(sprite,"setPosition",Qt::QueuedConnection,Q_ARG(QPointF,before));
            }else{
                QMetaObject::invokeMethod(sprite,"resetPenguin",Qt::QueuedConnection);
                movingSprites.remove(i.key());
            }

        }
        QThread::msleep(5);
    }
    movingSprites.clear();
    this->started = false;
    emit finished();
}


void PenguinSpriteMoveWorker::addToMovingSprites(AbstractCanvasObject* sprite, QPointF destination){
    movingSprites.insert(sprite, destination);
}
