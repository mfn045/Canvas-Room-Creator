#include "penguin.h"

Penguin::Penguin(Scene* parent) : parent(parent) {
    //parent->installEventFilter(this);
    connect(parent,SIGNAL(mouseMoved(QPointF)),this,SLOT(sceneMouseMoved(QPointF)));
    connect(parent,SIGNAL(mousePressed(QPointF)),this,SLOT(sceneMousePressed(QPointF)));
    setFlag(GraphicsItemFlag::ItemIsSelectable);

    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/South/penguin.svg",DIRECTION::S,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/South_West/penguin.svg",DIRECTION::SW,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/West/penguin.svg",DIRECTION::W,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/North_West/penguin.svg",DIRECTION::NW,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/North/penguin.svg",DIRECTION::N,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/North_East/penguin.svg",DIRECTION::NE,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/East/penguin.svg",DIRECTION::E,STATE::STANDING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Standing/South_East/penguin.svg",DIRECTION::SE,STATE::STANDING);

    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Waving",DIRECTION::S,STATE::WAVING);

    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/South",DIRECTION::S,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/South_West",DIRECTION::SW,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/West",DIRECTION::W,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/North_West",DIRECTION::NW,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/North",DIRECTION::N,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/North_East",DIRECTION::NE,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/East",DIRECTION::E,STATE::WALKING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Walking/South_East",DIRECTION::SE,STATE::WALKING);

    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/South",DIRECTION::S,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/South_West",DIRECTION::SW,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/West",DIRECTION::W,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/North_West",DIRECTION::NW,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/North",DIRECTION::N,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/North_East",DIRECTION::NE,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/East",DIRECTION::E,STATE::SITTING);
    initializeFrames("C:/Users/mfn45/OneDrive/Desktop/Penguin_States_Updated/Sitting/South_East",DIRECTION::SE,STATE::SITTING);

    changeColor("#660000");

    setVelocity(3);
    setScale(0.15);

    setIsMouseTrackable(true);
    setIsClickable(true);
    setIsHoverable(true);

    setCurrentFrames(DIRECTION::S,STATE::STANDING);
    setFrame(getCurrentFrame());
    setOrigin(QPointF(300,300));

}


void Penguin::sendChatBubble(QString msg){
    if(bubble == nullptr){
        bubble = new ChatBubble(this,msg);
    } else {
        delete bubble;
        bubble = new ChatBubble(this,msg);
        bubble->setText(msg);
    }
}

void Penguin::initializeFrames(QString filePath, DIRECTION direction, STATE state){
    if(filePath.isEmpty()) return;
    PENGUINPROPERTIES* p = nullptr;
    for(PROPERTIES* properties : getFrames().keys()){
        PENGUINPROPERTIES* penguinProperties = (PENGUINPROPERTIES*) properties;
        if(penguinProperties->direction == direction && penguinProperties->state == state){
            p = (PENGUINPROPERTIES*)properties;
        }
    }
    if(p == nullptr){
        p = new PENGUINPROPERTIES();
        p->direction = direction;
        p->state = state;
        p->filePath = filePath;
    }
    initFrames(filePath,p);
}

void Penguin::sceneMouseMoved(QPointF scenePos){
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


void Penguin::sceneMousePressed(QPointF posTemp){
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
    setFrame(getCurrentFrame());
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

void Penguin::sceneKeyPressed(int key){
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

void Penguin::setCurrentFrames(DIRECTION direction, STATE state){
    bool changed = false;
    for(PROPERTIES* properties : getFrames().keys()){
        PENGUINPROPERTIES* penguinProperties = (PENGUINPROPERTIES*) properties;
        if(penguinProperties->direction == direction && penguinProperties->state == state){
            CanvasObject::setCurrentFrames(properties);
            changed = true;
        }
    }
    if(changed){
        this->currentDirection = direction;
        this->currentState = state;
    }
}

Penguin::DIRECTION Penguin::getCurrentDirection(){
    return this->currentDirection;
}

void Penguin::setCurrentDirection(DIRECTION direction){
    if(direction != this->currentDirection){
        setCurrentFrames(direction,this->currentState);
        setFrame(getCurrentFrame());
        QList<QGraphicsItem*> children = childItems();
        for(QGraphicsItem* child : children){
            Penguin* childObj = (Penguin*)child;
            childObj->setCurrentFrames(direction,this->currentState);
            childObj->setFrame(getCurrentFrame());
        }
    }
}

Penguin::STATE Penguin::getCurrentState(){
    return this->currentState;
}

void Penguin::setCurrentState(STATE state){
    setCurrentFrames(this->currentDirection,state);
    setFrame(getCurrentFrame());
}

void Penguin::animationDone(){
    setCurrentFrames(getCurrentDirection(),STATE::STANDING);
    setIsMouseTrackable(true);
    setFrame(0);
}

double Penguin::getVelocity(){
    return this->velocity;
}
double Penguin::setVelocity(double velocity){
    this->velocity = velocity;
    return this->velocity;
}

void Penguin::walkTo(QPointF toPos){
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

void Penguin::resetPenguin(){
    setCurrentFrames(getCurrentDirection(),STATE::STANDING);
    setIsMouseTrackable(true);
    setFrame(0);
}

void Penguin::setPosition(QPointF pos){
    setPos(pos);
}

void Penguin::changeColor(QString color){
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


void Penguin::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    return QGraphicsItem::keyPressEvent(event);
}

void Penguin::mousePressEvent(QGraphicsSceneMouseEvent *event){

    return QGraphicsItem::mousePressEvent(event);
}

/*bool Penguin::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = (QKeyEvent*)event;
        int key = keyEvent->key();
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
    }else if(event->type() == QEvent::MouseButtonPress){
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
                /*QList<QGraphicsView*> views = scene()->views();
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
    }
    return QObject::eventFilter(watched,event);
}*/

Penguin::STATE Penguin::getStateFromString(QString string){
    if(string.toLower() == "standing"){
        return STATE::STANDING;
    } else if(string.toLower() == "walking"){
        return STATE::WALKING;
    } else if(string.toLower() == "dancing"){
        return STATE::DANCING;
    } else if(string.toLower() == "sitting"){
        return STATE::SITTING;
    } else if(string.toLower() == "waving"){
        return STATE::WAVING;
    }
}
