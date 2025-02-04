#include "penguinsprite.h"

PenguinSprite::PenguinSprite(Scene* parent) : parent(parent) {
    parent->installEventFilter(this);
    connect(parent,SIGNAL(mouseMoved(QPointF)),this,SLOT(sceneMouseMoved(QPointF)));
    connect(parent,SIGNAL(mousePressed(QPointF)),this,SLOT(sceneMousePressed(QPointF)));
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemStacksBehindParent);

    QString directory = "C:/Users/mfn45/OneDrive/Desktop/penguin_old_export/frames/output/";

    initializeFrames(directory+"1",DIRECTION::S,STATE::STANDING);
    initializeFrames(directory+"2",DIRECTION::SW,STATE::STANDING);
    initializeFrames(directory+"3",DIRECTION::W,STATE::STANDING);
    initializeFrames(directory+"4",DIRECTION::NW,STATE::STANDING);
    initializeFrames(directory+"5",DIRECTION::N,STATE::STANDING);
    initializeFrames(directory+"6",DIRECTION::NE,STATE::STANDING);
    initializeFrames(directory+"7",DIRECTION::E,STATE::STANDING);
    initializeFrames(directory+"8",DIRECTION::SE,STATE::STANDING);

    initializeFrames(directory+"9",DIRECTION::S,STATE::WALKING);
    initializeFrames(directory+"10",DIRECTION::SW,STATE::WALKING);
    initializeFrames(directory+"11",DIRECTION::W,STATE::WALKING);
    initializeFrames(directory+"12",DIRECTION::NW,STATE::WALKING);
    initializeFrames(directory+"13",DIRECTION::N,STATE::WALKING);
    initializeFrames(directory+"14",DIRECTION::NE,STATE::WALKING);
    initializeFrames(directory+"15",DIRECTION::E,STATE::WALKING);
    initializeFrames(directory+"16",DIRECTION::SE,STATE::WALKING);

    initializeFrames(directory+"17",DIRECTION::S,STATE::SITTING);
    initializeFrames(directory+"18",DIRECTION::SW,STATE::SITTING);
    initializeFrames(directory+"19",DIRECTION::W,STATE::SITTING);
    initializeFrames(directory+"20",DIRECTION::NW,STATE::SITTING);
    initializeFrames(directory+"21",DIRECTION::N,STATE::SITTING);
    initializeFrames(directory+"22",DIRECTION::NE,STATE::SITTING);
    initializeFrames(directory+"23",DIRECTION::E,STATE::SITTING);
    initializeFrames(directory+"24",DIRECTION::SE,STATE::SITTING);

    initializeFrames(directory+"25",DIRECTION::S,STATE::WAVING);
    initializeFrames(directory+"26",DIRECTION::S,STATE::DANCING);

    setVelocity(3);

    setIsMouseTrackable(true);
    setIsClickable(true);
    setIsHoverable(true);

    setCurrentFrames(DIRECTION::S,STATE::STANDING);
    setFrame(getCurrentFrame());
    setOrigin(QPointF(32.5,32.5));

    changeColor("#660000");

}


void PenguinSprite::sendChatBubble(QString msg){
    if(bubble == nullptr){
        bubble = new ChatBubble(this,msg);
    } else {
        delete bubble;
        bubble = new ChatBubble(this,msg);
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
    setCurrentFrames(direction,STATE::WALKING);
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
    walkTo(posTemp);
}

void PenguinSprite::sceneKeyPressed(int key){
    if(key == Qt::Key_W){
        if(getCurrentState() != STATE::WALKING){
            setIsMouseTrackable(false);
            setHasAnimationLoop(false);
            setCurrentFrames(DIRECTION::S,STATE::WAVING);
            setFrame(getCurrentFrame());
        }
    }else if(key == Qt::Key_I){
        if(getCurrentState() != STATE::WALKING){
            if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::N){
                resetPenguin();
            }else{
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentFrames(DIRECTION::N,STATE::SITTING);
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
                setCurrentFrames(DIRECTION::S,STATE::SITTING);
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
                setCurrentFrames(DIRECTION::W,STATE::SITTING);
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
                setCurrentFrames(DIRECTION::E,STATE::SITTING);
                setFrame(getCurrentFrame());
            }
        }
    }
}

void PenguinSprite::animationDone(){
    setCurrentFrames(getCurrentDirection(),STATE::STANDING);
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

void PenguinSprite::walkTo(QPointF toPos){
    QPointF currentPos = pos();
    double x_add = 1;
    double y_add = 1;
    if(currentPos.x() > toPos.x()){
        x_add*=-1;
    }
    if(currentPos.y() > toPos.y()){
        y_add*=-1;
    }
    if(thread != nullptr){
        thread->terminate();
    }
    thread = QThread::create([this](QPointF before, QPointF after, double x_add, double y_add){
        double y_diff = after.y() - before.y();
        double x_diff = after.x() - before.x();
        double length = sqrt(pow(y_diff,2)+pow(x_diff,2));
        double normalized_y = y_diff/length;
        double normalized_x = x_diff/length;
        double velocity = getVelocity();
        while(before != after){
            if(before.x() != after.x()){
                before.setX(before.x()+normalized_x*velocity);
                if(x_add == 1){
                    if(before.x() > after.x()){
                        before.setX(after.x());
                    }
                }else if(x_add == -1){
                    if(before.x() < after.x()){
                        before.setX(after.x());
                    }
                }
            }
            if(before.y() != after.y()){
                before.setY(before.y()+normalized_y*velocity);
                if(y_add == 1){
                    if(before.y() > after.y()){
                        before.setY(after.y());
                    }
                }else if(y_add == -1){
                    if(before.y() < after.y()){
                        before.setY(after.y());
                    }
                }
            }
            QMetaObject::invokeMethod(this,"setPosition",Qt::QueuedConnection, Q_ARG(QPointF,before));
            QThread::msleep(5);
        }
        QMetaObject::invokeMethod(this,"resetPenguin", Qt::QueuedConnection);
    }, currentPos, toPos,x_add,y_add);
    thread->start();
}

void PenguinSprite::resetPenguin(){
    setCurrentFrames(getCurrentDirection(),STATE::STANDING);
    setIsMouseTrackable(true);
    setFrame(0);
}

void PenguinSprite::setPosition(QPointF pos){
    setPos(pos);
}

void PenguinSprite::changeColor(QString color){
    QDomDocument doc;
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
    }
}

PenguinSpriteClothing* PenguinSprite::loadItem(int id){
    PenguinSpriteClothing* item = new PenguinSpriteClothing(this);
    QString directory = "C:/Users/mfn45/OneDrive/Desktop/Clothings/1-499/sprite_export/output/" + QString::number(id) + "/";

    item->initializeFrames(directory+"1",DIRECTION::S,STATE::STANDING);
    item->initializeFrames(directory+"2",DIRECTION::SW,STATE::STANDING);
    item->initializeFrames(directory+"3",DIRECTION::W,STATE::STANDING);
    item->initializeFrames(directory+"4",DIRECTION::NW,STATE::STANDING);
    item->initializeFrames(directory+"5",DIRECTION::N,STATE::STANDING);
    item->initializeFrames(directory+"6",DIRECTION::NE,STATE::STANDING);
    item->initializeFrames(directory+"7",DIRECTION::E,STATE::STANDING);
    item->initializeFrames(directory+"8",DIRECTION::SE,STATE::STANDING);

    item->initializeFrames(directory+"9",DIRECTION::S,STATE::WALKING);
    item->initializeFrames(directory+"10",DIRECTION::SW,STATE::WALKING);
    item->initializeFrames(directory+"11",DIRECTION::W,STATE::WALKING);
    item->initializeFrames(directory+"12",DIRECTION::NW,STATE::WALKING);
    item->initializeFrames(directory+"13",DIRECTION::N,STATE::WALKING);
    item->initializeFrames(directory+"14",DIRECTION::NE,STATE::WALKING);
    item->initializeFrames(directory+"15",DIRECTION::E,STATE::WALKING);
    item->initializeFrames(directory+"16",DIRECTION::SE,STATE::WALKING);

    item->initializeFrames(directory+"17",DIRECTION::S,STATE::SITTING);
    item->initializeFrames(directory+"18",DIRECTION::SW,STATE::SITTING);
    item->initializeFrames(directory+"19",DIRECTION::W,STATE::SITTING);
    item->initializeFrames(directory+"20",DIRECTION::NW,STATE::SITTING);
    item->initializeFrames(directory+"21",DIRECTION::N,STATE::SITTING);
    item->initializeFrames(directory+"22",DIRECTION::NE,STATE::SITTING);
    item->initializeFrames(directory+"23",DIRECTION::E,STATE::SITTING);
    item->initializeFrames(directory+"24",DIRECTION::SE,STATE::SITTING);

    item->initializeFrames(directory+"25",DIRECTION::S,STATE::WAVING);
    item->initializeFrames(directory+"26",DIRECTION::S,STATE::DANCING);


    item->setCurrentFrames(getCurrentDirection(),getCurrentState());
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

void PenguinSprite::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    return QGraphicsItem::keyPressEvent(event);
}

void PenguinSprite::mousePressEvent(QGraphicsSceneMouseEvent *event){

    return QGraphicsItem::mousePressEvent(event);
}

bool PenguinSprite::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = (QKeyEvent*)event;
        int key = keyEvent->key();
        if(key == Qt::Key_W){
            if(getCurrentState() != STATE::WALKING){
                setIsMouseTrackable(false);
                setHasAnimationLoop(false);
                setCurrentFrames(DIRECTION::S,STATE::WAVING);
            }
        } else if(key == Qt::Key_D){
            if(getCurrentState() != STATE::WALKING){
                setIsMouseTrackable(false);
                setHasAnimationLoop(true);
                setCurrentFrames(DIRECTION::S,STATE::DANCING);
            }
        }else if(key == Qt::Key_I){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::N){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentFrames(DIRECTION::N,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_K){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::S){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentFrames(DIRECTION::S,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_J){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::W){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentFrames(DIRECTION::W,STATE::SITTING);
                }
            }
        }else if(key == Qt::Key_L){
            if(getCurrentState() != STATE::WALKING){
                if(getCurrentState() == STATE::SITTING && getCurrentDirection() == DIRECTION::E){
                    resetPenguin();
                }else{
                    setIsMouseTrackable(false);
                    setHasAnimationLoop(false);
                    setCurrentFrames(DIRECTION::E,STATE::SITTING);
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
                setCurrentFrames(direction,STATE::WALKING);
                setFrame(getCurrentFrame());
                posTemp.setX(posTemp.x()+(pos().x()-mapToParent(getOrigin()).x()));
                posTemp.setY(posTemp.y()+(pos().y()-mapToParent(getOrigin()).y()));
                walkTo(posTemp);
        }
    }*/
    return QObject::eventFilter(watched,event);
}
