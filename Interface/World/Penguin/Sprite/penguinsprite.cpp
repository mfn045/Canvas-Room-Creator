#include "penguinsprite.h"

PenguinSprite::PenguinSprite() {
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemStacksBehindParent);

    AssetsManager* am = AssetsManager::getInstance();
    initFrames(am->getAssetPath("interface.world.penguin.penguinsprite"));

    setVelocity(3);

    setIsMouseTrackable(true);
    setIsClickable(true);
    setIsHoverable(true);

    setCurrentSprite(DIRECTION::S,STATE::STANDING);
    setFrame(getCurrentFrame());
    setOrigin(QPointF(50,50));

    changeColor("#660000");

}

void PenguinSprite::initializeEvents(Scene* parent){
    this->parent = parent;
    parent->installEventFilter(this);
    connect(parent,SIGNAL(mouseMoved(QPointF)),this,SLOT(sceneMouseMoved(QPointF)));
    connect(parent,SIGNAL(mousePressed(QPointF)),this,SLOT(sceneMousePressed(QPointF)));
}

void PenguinSprite::uninitializeEvents(){
    parent->removeEventFilter(this);
    disconnect(parent,SIGNAL(mouseMoved(QPointF)),this,SLOT(sceneMouseMoved(QPointF)));
    disconnect(parent,SIGNAL(mousePressed(QPointF)),this,SLOT(sceneMousePressed(QPointF)));
    this->parent = nullptr;
}

PenguinSprite::~PenguinSprite(){

}

void PenguinSprite::sendChatBubble(QString msg){
    if(bubble == nullptr){
        //bubble = new ChatBubble(this,msg);
    } else {
        delete bubble;
        //bubble = new ChatBubble(this,msg);
        bubble->setText(msg);
    }
}

void PenguinSprite::sceneMouseMoved(QPointF scenePos){
    if(isMouseTrackable()){
            DIRECTION direction = DIRECTION::S;
            QPointF origin(0,0);
            if(getOrigin().isNull()){
                origin = pos();
            }else {
                QTransform transform = sceneTransform();
                transform.setMatrix(transform.m11(),transform.m12(),transform.m13(),
                                                transform.m21(),transform.m22(),transform.m23(),
                                                0,0,transform.m33());
                QPointF storedOrigin = getOrigin()*transform;
                double x = pos().x()+storedOrigin.x();
                double y = pos().y()+storedOrigin.y();
                origin = QPointF(x,y);
            }
            int x = scenePos.x()-origin.x();
            int y = scenePos.y()-origin.y();
            double angle = y != 0 ? atan2(x,y)*180/3.14591 : 90;
            if(y==0 && x < 0){
                angle*=-1;
            }
            if(-180 < angle && angle < -157.5){
                direction = DIRECTION::N;
                //qDebug() << "NORTH --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            } else if(-157.5 < angle && angle < -112.5){
                direction = DIRECTION::NW;
                //qDebug() << "NORTH/WEST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            } else if(-112.5 < angle && angle < -67.5){
                direction = DIRECTION::W;
                //qDebug() << "WEST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            } else if(-67.5 < angle && angle < -22.5){
                direction = DIRECTION::SW;
                //qDebug() << "SOUTH/WEST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            } else if(22.5 > angle && angle > -22.5){
                direction = DIRECTION::S;
                //qDebug() << "SOUTH --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            }else if(67.5 > angle && angle > 22.5){
                direction = DIRECTION::SE;
                //qDebug() << "SOUTH/EAST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            }else if(112.5 > angle && angle > 67.5){
                direction = DIRECTION::E;
                //qDebug() << "EAST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            }else if(157.5 > angle && angle > 112.5){
                direction = DIRECTION::NE;
                //qDebug() << "NORTH/EAST --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            }else if(180 > angle && angle > 157.5){
                direction = DIRECTION::N;
                //qDebug() << "NORTH --> " << obj->pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
            }
            setCurrentDirection(direction);
    }
}


void PenguinSprite::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(!isTransparentPixel(event->pos())){
        emit clickedPenguin();
    }

}

void PenguinSprite::sceneMousePressed(QPointF posTemp){
    setIsMouseTrackable(false);
    setHasAnimationLoop(true);
    DIRECTION direction = DIRECTION::S;
    QPointF origin(0,0);
    if(getOrigin().isNull()){
        origin = pos();
    }else {
        QTransform transform = sceneTransform();
        transform.setMatrix(transform.m11(),transform.m12(),transform.m13(),
                            transform.m21(),transform.m22(),transform.m23(),
                            0,0,transform.m33());
        QPointF storedOrigin = getOrigin()*transform;
        double x = pos().x()+storedOrigin.x();
        double y = pos().y()+storedOrigin.y();
        origin = QPointF(x,y);
    }
    int x = posTemp.x()-origin.x();
    int y = posTemp.y()-origin.y();
    double angle = y != 0 ? atan2(x,y)*180/3.14591 : 90;
    if(y==0 && x < 0){
        angle*=-1;
    }
    if(-180 < angle && angle < -157.5){
        direction = DIRECTION::N;
        //qDebug() << "NORTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    } else if(-157.5 < angle && angle < -112.5){
        direction = DIRECTION::NW;
        //qDebug() << "NORTH/WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    } else if(-112.5 < angle && angle < -67.5){
        direction = DIRECTION::W;
        //qDebug() << "WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    } else if(-67.5 < angle && angle < -22.5){
        direction = DIRECTION::SW;
        //qDebug() << "SOUTH/WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    } else if(22.5 > angle && angle > -22.5){
        direction = DIRECTION::S;
        //qDebug() << "SOUTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    }else if(67.5 > angle && angle > 22.5){
        direction = DIRECTION::SE;
        //qDebug() << "SOUTH/EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    }else if(112.5 > angle && angle > 67.5){
        direction = DIRECTION::E;
        //qDebug() << "EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    }else if(157.5 > angle && angle > 112.5){
        direction = DIRECTION::NE;
        //qDebug() << "NORTH/EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    }else if(180 > angle && angle > 157.5){
        direction = DIRECTION::N;
        //qDebug() << "NORTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
    }
    setCurrentSprite(direction,STATE::WALKING);
    posTemp.setX(posTemp.x()+(pos().x()-mapToParent(getOrigin()).x()));
    posTemp.setY(posTemp.y()+(pos().y()-mapToParent(getOrigin()).y()));

    if(posTemp.x() > scene()->width()){
        posTemp.setX(scene()->width());
    }else if(posTemp.x() < 0){
        posTemp.setX(0);
    }
    if(posTemp.y() > scene()->height()){
        posTemp.setY(scene()->height());
    }else if(posTemp.y() < 0){
        posTemp.setY(0);
    }
    //setDestination(posTemp);
    //emit changedDestination();
    walkTo(posTemp);
}

void PenguinSprite::sceneKeyPressed(int key){
    if(key == Qt::Key_W){
        if(getCurrentState() != STATE::WALKING){
            setIsMouseTrackable(false);
            setHasAnimationLoop(false);
            setCurrentSprite(DIRECTION::S,STATE::WAVING);
            setFrame(getCurrentFrame());
        }
    }else if(key == Qt::Key_I){
        if(getCurrentState() != STATE::WALKING){
            if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::N){
                resetPenguin();
            }else{
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentSprite(DIRECTION::N,STATE::SITTING);
                setFrame(getCurrentFrame());
            }
        }
    }else if(key == Qt::Key_K){
        if(getCurrentState() != STATE::WALKING){
            if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::S){
                resetPenguin();
            }else{
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentSprite(DIRECTION::S,STATE::SITTING);
                setFrame(getCurrentFrame());
            }
        }
    }else if(key == Qt::Key_J){
        if(getCurrentState() != STATE::WALKING){
            if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::W){
                resetPenguin();
            }else{
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentSprite(DIRECTION::W,STATE::SITTING);
                setFrame(getCurrentFrame());
            }
        }
    }else if(key == Qt::Key_L){
        if(getCurrentState() != STATE::WALKING){
            if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::E){
                resetPenguin();
            }else{
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentSprite(DIRECTION::E,STATE::SITTING);
                setFrame(getCurrentFrame());
            }
        }
    }
}

void PenguinSprite::animationDone(){
    setCurrentSprite(getCurrentDirection(),STATE::STANDING);
    setIsMouseTrackable(true);
    setFrame(0);
}

double PenguinSprite::getVelocity(){
    return this->velocity;
}
double PenguinSprite::setVelocity(double velocity){
    this->velocity = velocity;
    return this->velocity;
}

QPointF PenguinSprite::getDestination(){
    return this->destination;
}
QPointF PenguinSprite::setDestination(QPointF destination){
    this->destination = destination;
    return this->destination;
}

void PenguinSprite::walkTo(QPointF after){
    ThreadPoolManager* tpm = ThreadPoolManager::getInstance();
    PenguinSpriteMoveWorker* worker = tpm->getPSMW();
    worker->addToMovingSprites(this,after);
    if(!worker->hasStarted()){
        connect(worker,&PenguinSpriteMoveWorker::finished,[tpm, worker](){
            if(tpm && worker){
                tpm->resetPSMW();
            }
        });
        tpm->start(worker);
    }
}

void PenguinSprite::resetPenguin(){
    setCurrentSprite(getCurrentDirection(),STATE::STANDING);
    setIsMouseTrackable(true);
    setFrame(0);
}

void PenguinSprite::setPosition(QPointF pos){
    setPos(pos);
}

void PenguinSprite::changeColor(QString color){
    /*QDomDocument doc;
    for(auto it = getFrames().begin(); it != getFrames().end(); it++){
        for(QByteArray* ba : it.value()){
            doc.setContent(*ba);
            QDomElement docElement = doc.documentElement();
            QDomElement docChildElement = docElement.firstChildElement();
            while(!docChildElement.isNull()){
                if(docChildElement.attribute("id") == "penguin"){
                    break;
                }
                docChildElement = docChildElement.nextSiblingElement();
            }
            QDomElement targetElement = docChildElement.firstChildElement();

            while (!targetElement.isNull()) {
                if (targetElement.attribute("id") == "body") {
                    break;
                }
                targetElement = targetElement.nextSiblingElement();
            }
            QDomElement childOfTarget = targetElement.firstChildElement();
            while (!childOfTarget.isNull()) {
                if (childOfTarget.hasAttribute("fill")) {
                    childOfTarget.setAttribute("fill",color);
                }
                childOfTarget = childOfTarget.nextSiblingElement();
            }
            *ba = doc.toByteArray();
        }
    }*/
}

PenguinSpriteClothing* PenguinSprite::loadItem(int id){
    PenguinSpriteClothing* item = new PenguinSpriteClothing(this);
    QString directory = "C:/Users/mfn45/OneDrive/Desktop/Clothings/1-499/sprite_export/output/" + QString::number(id) + "/";
    item->initFrames(directory);
    item->setCurrentSprite(getCurrentDirection(),getCurrentState());
    item->setFrame(getCurrentFrame());
    return item;
}

void PenguinSprite::setHead(int headId){
    bool exists = false;
    if(head == nullptr){
        head = loadItem(headId);
    }else {
        exists = true;
    }
    if(exists){
        delete head;
        head = loadItem(headId);
    }
    head->setZValue(6);
    qDebug() << "HEAD IS " << head;
}

void PenguinSprite::setFace(int faceId){
    bool exists = false;
    if(face == nullptr){
        face = loadItem(faceId);
    }else {
        exists = true;
    }
    if(exists){
        delete face;
        face = loadItem(faceId);
    }
    face->setZValue(5);
}

void PenguinSprite::setNeck(int neckId){
    bool exists = false;
    if(neck == nullptr){
        neck = loadItem(neckId);
    }else {
        exists = true;
    }
    if(exists){
        delete neck;
        neck = loadItem(neckId);
    }
    neck->setZValue(4);
}

void PenguinSprite::setBody(int bodyId){
    bool exists = false;
    if(body == nullptr){
        body = loadItem(bodyId);
    }else {
        exists = true;
    }
    if(exists){
        delete body;
        body = loadItem(bodyId);
    }
    body->setZValue(3);
}

void PenguinSprite::setHand(int handId){
    bool exists = false;
    if(hand == nullptr){
        hand = loadItem(handId);
    }else {
        exists = true;
    }
    if(exists){
        delete hand;
        hand = loadItem(handId);
    }
    hand->setZValue(8);
}

void PenguinSprite::setFeet(int feetId){
    bool exists = false;
    if(feet == nullptr){
        feet = loadItem(feetId);
    }else {
        exists = true;
    }
    if(exists){
        delete feet;
        feet = loadItem(feetId);
    }
    feet->setZValue(2);
    qDebug() << "feet IS " << feet;
}

bool PenguinSprite::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = (QKeyEvent*)event;
        int key = keyEvent->key();
        if(key == Qt::Key_W){
            if(getCurrentState() != STATE::WALKING){
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentSprite(DIRECTION::S,STATE::WAVING);
            }
        } else if(key == Qt::Key_D){
            if(getCurrentState() != STATE::WALKING){
                setIsMouseTrackable(false);
                setHasAnimationLoop(true);
                setCurrentSprite(DIRECTION::S,STATE::DANCING);
            }
        }else if(key == Qt::Key_I){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::N){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentSprite(DIRECTION::N,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_K){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::S){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentSprite(DIRECTION::S,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_J){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::W){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentSprite(DIRECTION::W,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_L){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::E){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentSprite(DIRECTION::E,STATE::SITTING);
                }
            }
        }
    }/*else if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        if(mouseEvent->button() == Qt::LeftButton){
            qDebug() << " AYYY LEFTTTT ------";
                setIsMouseTrackable(false);
                setHasAnimationLoop(true);
                DIRECTION direction = DIRECTION::S;
                //QPointF origin = getOrigin().isNull() ? pos() : mapToParent(getOrigin());
                QPointF origin(0,0);
                if(getOrigin().isNull()){
                    origin = pos();
                    qDebug() << "1" <<origin;
                }else {
                    QPointF storedOrigin = getOrigin();
                    double x = pos().x()+boundingRect().width()*storedOrigin.x();
                    double y = pos().y()+boundingRect().width()*storedOrigin.y();
                    origin = mapToParent(QPointF(x,y));
                    qDebug() << "2" <<  origin;
                }
                QPointF posTemp(0,0);
                /&QList<QGraphicsView*> views = scene()->views();
                QGraphicsView* view = nullptr;
                if (!views.isEmpty()) {
                    view= views.first();
                    posTemp = view->mapFrom(parent,mouseEvent->pos());
                }*
                posTemp = mouseEvent->pos();
                int x = posTemp.x()-origin.x();
                int y = posTemp.y()-origin.y();
                double angle = y != 0 ? atan2(x,y)*180/3.14591 : 90;
                if(y==0 && x < 0){
                    angle*=-1;
                }
                if(-180 < angle && angle < -157.5){
                    direction = DIRECTION::N;
                    //qDebug() << "NORTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                } else if(-157.5 < angle && angle < -112.5){
                    direction = DIRECTION::NW;
                    //qDebug() << "NORTH/WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                } else if(-112.5 < angle && angle < -67.5){
                    direction = DIRECTION::W;
                    //qDebug() << "WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                } else if(-67.5 < angle && angle < -22.5){
                    direction = DIRECTION::SW;
                    //qDebug() << "SOUTH/WEST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                } else if(22.5 > angle && angle > -22.5){
                    direction = DIRECTION::S;
                    //qDebug() << "SOUTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                }else if(67.5 > angle && angle > 22.5){
                    direction = DIRECTION::SE;
                    //qDebug() << "SOUTH/EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                }else if(112.5 > angle && angle > 67.5){
                    direction = DIRECTION::E;
                    //qDebug() << "EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                }else if(157.5 > angle && angle > 112.5){
                    direction = DIRECTION::NE;
                    //qDebug() << "NORTH/EAST --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                }else if(180 > angle && angle > 157.5){
                    direction = DIRECTION::N;
                    //qDebug() << "NORTH --> " << pos() << ", " << "x: " << x << "," << "y: " << y << "," << pos << ", " << angle;
                }
                setCurrentSprite(direction,STATE::WALKING);
                setFrame(getCurrentFrame());
                posTemp.setX(posTemp.x()+(pos().x()-mapToParent(getOrigin()).x()));
                posTemp.setY(posTemp.y()+(pos().y()-mapToParent(getOrigin()).y()));
                walkTo(posTemp);
        }
    }*/
    return QObject::eventFilter(watched,event);
}
